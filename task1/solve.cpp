//
// Created by alex on 29.09.2021.
//

#include "solve.h"

using RegLenType = std::set<std::pair<int, int>>;

int gcd(int t1, int t2) {
    int min = std::min(t1, t2);
    int max = std::max(t1, t2);
    if (min == 0)return max;
    while (max % min) {
        max %= min;
        std::swap(min, max);
    }
    return min;
}

RegLenType sum(RegLenType t1, RegLenType& t2) {
    t1.merge(t2);
    return t1;
}

RegLenType concat(RegLenType& t1, RegLenType& t2) {
    RegLenType result;
    for (auto& i:t1) for (auto& j:t2) result.insert({i.first + j.first, gcd(i.second, j.second)});
    return result;
}

RegLenType star(const RegLenType& t) {
    int allGcd = t.begin()->first;
    for (auto& i:t) allGcd = gcd(allGcd, gcd(i.first, i.second));
    return {{0, allGcd}};
}

std::string solve(const std::string& regularExpression, int k, int l) {
    if(k==0) return "ERROR";
    std::vector<RegLenType> stack;
    for (char c : regularExpression) {
        if (c == '1') stack.push_back({{0, 0}});
        else if (c <= 'c' && c >= 'a') stack.push_back({{1, 0}});
        else {
            if (stack.empty()) return "ERROR";
            RegLenType first = stack.back();
            stack.pop_back();
            if (c == '*') stack.push_back(star(first));
            else {
                if (stack.empty()) return "ERROR";
                RegLenType second = stack.back();
                stack.pop_back();
                if (c == '+') stack.push_back(sum(first, second));
                else if (c == '.') stack.push_back(concat(first, second));
                else return "ERROR";
            }
        }
    }
    if (stack.size() != 1) return "ERROR";
    for (auto t:stack.back()) {
        t.second = gcd(k, t.second);
        if (t.second == 0) { if ((l - t.first) % k == 0) return "YES"; }
        else if ((l - t.first + k) % t.second == 0) return "YES";
    }
    return "NO";
}