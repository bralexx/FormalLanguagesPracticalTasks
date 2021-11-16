#include <gtest/gtest.h>
#include "Grammar.h"
#include <vector>
#include <string>

TEST(SimpleTests, test_from_neerc) {
    Grammar g({'S', 'T', 'F'}, {'+', '*', '(', ')', 'a'}, {{'S', "T+S"},
                                                           {'S', "T+S"},
                                                           {'S', "T"},
                                                           {'T', "F*T"},
                                                           {'T', "F"},
                                                           {'F', "(S)"},
                                                           {'F', "a"}});
    EXPECT_EQ(g.earley("(a+a)"), true);
    EXPECT_EQ(g.earley("(a+a+a)"), true);
    EXPECT_EQ(g.earley("(a+a*a)"), true);
    EXPECT_EQ(g.earley("(a+a)*a)"), false);
    EXPECT_EQ(g.earley("((a+a)*a)"), true);
}


TEST(Arithmetic, test1) {
    std::vector<char> notTerm = {'S', 'N', 'n'};
    std::vector<char> term = {'(', ')', '+', '-', '*', '/'};
    for (int i = 0; i < 10; ++i) term.push_back(i + '0');
    std::vector<std::pair<char, std::string>> rules = {{'S', "S+S"},
                                                       {'S', "S-S"},
                                                       {'S', "S*S"},
                                                       {'S', "S/S"},
                                                       {'S', "(S)"},
                                                       {'S', "(-S)"},
                                                       {'S', "N"},
                                                       {'S', "0"},
                                                       {'N', "Nn"},
                                                       {'N', "N0"},
                                                       {'N', "n"},
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
    EXPECT_EQ(g.earley("0"), true);
    EXPECT_EQ(g.earley("1"), true);
    EXPECT_EQ(g.earley("10"), true);
    EXPECT_EQ(g.earley("1234567890+987654321"), true);
    EXPECT_EQ(g.earley("(2*3)-4/2+215*2435/124"), true);
    EXPECT_EQ(g.earley("(2)*(9-(1+4))/(123-123)+(12)"), true);
    EXPECT_EQ(g.earley("134/21345/3245/3425/3425/4325/324/5432/3245"), true);
    EXPECT_EQ(g.earley("2+2-2+2"), true);
    EXPECT_EQ(g.earley("2*(3+435)/2"), true);
    EXPECT_EQ(g.earley("2*(-2)"), true);
    EXPECT_EQ(g.earley(
            "2+5+4-6+4+1+2+3+4+5+6-8+9+0-0+9+8+7*6+5+4+3+2+(1+3)+5-6+5/4*6+5-4+6+(((5+3)+6+4)+3+6)+5+3+4+6+5+3+4+6+5+4+4+2+3+2"),
            true);
    EXPECT_EQ(g.earley("01"), false);
    EXPECT_EQ(g.earley("0345342532"), false);
    EXPECT_EQ(g.earley("()"), false);
    EXPECT_EQ(g.earley("2*-2"), false);
    EXPECT_EQ(g.earley("(2+(21*7)"), false);
    EXPECT_EQ(g.earley("6+-1"), false);
    EXPECT_EQ(g.earley("34534+"), false);
    EXPECT_EQ(g.earley("+7890"), false);
    std::vector<std::string> tests;
    std::srand(std::time(nullptr));
    for(int i = 1; i < 50; ++i)
        tests.push_back(std::to_string(i*(rand()%1000)));
    for(int i = 0; i < 100; ++i) {
        int l = rand()%tests.size();
        int r = rand()%tests.size();
        tests.push_back(tests[l]+'+'+tests[r]);
        tests.push_back(tests[l]+'*'+tests[r]);
        tests.push_back('('+tests[l]+')'+'/'+tests[r]);
        tests.push_back("(-"+tests[l]+')');
        tests.push_back(tests[l]+'-'+tests[r]);
    }
    for(auto& test:tests)
        EXPECT_EQ(g.earley(test), true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}