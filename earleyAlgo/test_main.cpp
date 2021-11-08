#include <gtest/gtest.h>
#include "Grammar.h"
#include <vector>
#include <string>

TEST(Simple_test, test1) {
    Grammar g({'S', 'T', 'F'}, {'+', '*', '(', ')', 'a'}, {{'S', "T+S"},
                                                           {'S', "T+S"},
                                                           {'S', "T"},
                                                           {'T', "F*T"},
                                                           {'T', "F"},
                                                           {'F', "(S)"},
                                                           {'F', "a"}});
//EXPECT_EQ(g.euler("(a+a)"),true);
//EXPECT_EQ(g.euler("(a+a+a)"),true);
}


TEST(Arithmetic, lol) {
    std::vector<char> notTerm = {'S', 'N', 'n'};
    std::vector<char> term = {'(', ')', '+', '-', '*', '/'};
    for (int i = 0; i < 10; ++i) term.push_back(i + '0');
    std::vector<std::pair<char, std::string>> rules = {{'S', "S+S"},
                                                       {'S', "S-S"},
                                                       {'S', "S*S"},
                                                       {'S', "S/S"},
                                                       {'S', "(S)"},
                                                       {'S', "N"},
                                                       {'N', "Nn"},
                                                       {'N', "n"},
                                                       {'n', "0"},
                                                       {'n', "1"},
                                                       {'n', "2"},
                                                       {'n', "3"},
                                                       {'n', "4"},
                                                       {'n', "5"},
                                                       {'n', "6"},
                                                       {'n', "7"},
                                                       {'n', "8"},
                                                       {'n', "9"},
    };
    Grammar g(notTerm, term, rules);
    EXPECT_EQ(g.euler("2"), true);
    EXPECT_EQ(g.euler("2*(3+435)/2"), true);
    EXPECT_EQ(
            g.euler("2+5+4+6+4+1+2+3+4+5+6+8+9+0+0+9+8+7+6+5+4+3+2+1+3+5+6+5+4+6+5+4+6+5+3+6+4+3+6+5+3+4+6+5+3+4+6+5+4+4+2+3+2"),
            true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}