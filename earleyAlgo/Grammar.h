//
// Created by alex on 08.11.2021.
//

#ifndef EARLEYALGO_GRAMMAR_H
#define EARLEYALGO_GRAMMAR_H

#include <unordered_map>
#include <vector>
#include <set>

class Grammar {
    struct Symbol {
        char letter;
        bool term;
    };
    std::vector<Symbol> symbols;
    std::unordered_map<char, int> char2SymbolTable;
    struct Rule {
        int left;
        std::vector<int> right;
    };
    std::vector<std::vector<Rule>> rules;

    struct Situation {
        std::pair<int, int> rule;
        int i;
        int dotPos;

        bool operator<(const Situation&) const;
    };

    struct D {
        std::set<Situation> termAfterDot;
        std::set<Situation> nothingAfterDot;
        std::set<Situation> notTermAfterDot;
    };
    std::vector<D> DList;

    void addToD(int, Situation);

    void scan(int, const std::string&);

    void complete(int, const std::string&);

    void predict(int, const std::string&);

public:
    Grammar(const std::vector<char>& notTerms, const std::vector<char>& terms,
            const std::vector<std::pair<char, std::string>>& rules);

    bool euler(const std::string&);
};


#endif //EARLEYALGO_GRAMMAR_H
