#include <iostream>
#include "solve.h"

int main() {
    std::string s1 = "ab+c.aba.*.bac.+.+*";
    std::string s2 = "acb..bab.c.*.ab.ba.+.+*a.";
    std::cout << solve("aaaaa....*",3,0);
    return 0;
}
