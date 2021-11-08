//
// Created by alex on 08.11.2021.
//

#include "Grammar.h"

Grammar::Grammar(const std::vector<char>& notTerms, const std::vector<char>& terms,
                 const std::vector<std::pair<char, std::string>>& rulesInput) {
    symbols.push_back({-1, false});
    for (auto i:notTerms)
        symbols.push_back({i, false});
    for (auto i:terms)
        symbols.push_back({i, true});
    for (int i = 0; i < symbols.size(); ++i)
        char2SymbolTable[symbols[i].letter] = i;
    rules = std::vector<std::vector<Rule>>(notTerms.size() + 1);
    rules[0].push_back({0, {char2SymbolTable['S']}});
    for (auto i:rulesInput) {
        std::vector<int> right;
        for (auto j:i.second)
            right.push_back(char2SymbolTable[j]);
        rules[char2SymbolTable[i.first]].push_back({char2SymbolTable[i.first], right});
    }
}

bool Grammar::euler(const std::string& w) {
    DList = std::vector<D>(w.size() + 1);
    DList[0].notTermAfterDot.insert({{0, 0}, 0, 0});
    for (int j = 0; j < DList.size(); ++j) {
        scan(j, w);
        int sz = -1;
        while (DList[j].notTermAfterDot.size() + DList[j].nothingAfterDot.size() + DList[j].termAfterDot.size() != sz) {
            sz = DList[j].notTermAfterDot.size() + DList[j].nothingAfterDot.size() + DList[j].termAfterDot.size();
            complete(j, w);
            predict(j, w);
        }
    }
    for (auto i:DList[w.size()].nothingAfterDot)
        if (i.rule.first == 0 && i.rule.second == 0 && i.dotPos == 1 && i.i == 0)
            return true;
    return false;
}

void Grammar::scan(int j, const std::string& w) {
    if (j == 0)
        return;
    for (auto it = DList[j - 1].termAfterDot.begin(); it != DList[j - 1].termAfterDot.end(); ++it)
        if (symbols[rules[it->rule.first][it->rule.second].right[it->dotPos]].letter == w[j - 1]) {
            Situation st = *it;
            ++st.dotPos;
            addToD(j, st);
        }
}

void Grammar::addToD(int j, Grammar::Situation st) {
    if (rules[st.rule.first][st.rule.second].right.size() == st.dotPos)
        DList[j].nothingAfterDot.insert(st);
    else if (symbols[rules[st.rule.first][st.rule.second].right[st.dotPos]].term)
        DList[j].termAfterDot.insert(st);
    else
        DList[j].notTermAfterDot.insert(st);
}

void Grammar::complete(int j, const std::string& w) {
    for (auto st1:DList[j].nothingAfterDot)
        for (auto st2:DList[st1.i].notTermAfterDot) {
            Situation st = st2;
            ++st.dotPos;
            addToD(j, st);
        }
}

void Grammar::predict(int j, const std::string& w) {
    for (auto st1:DList[j].notTermAfterDot) {
        int r1 = rules[st1.rule.first][st1.rule.second].right[st1.dotPos];
        for (int r2 = 0; r2 < rules[r1].size(); ++r2) {
            Situation st = {{r1, r2}, j, 0};
            addToD(j, st);
        }
    }
}

bool Grammar::Situation::operator<(const Grammar::Situation& t2) const {
    return rule < t2.rule;
}
