#include <iostream>
#include "solve.h"

int main() {
    std::string s;
    int k, l;
    std::cin >> s >> k >> l;
    std::cout << solve(s, k, l);
    return 0;
}
