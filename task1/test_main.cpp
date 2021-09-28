#include <cassert>
#include "solve.h"

int main() {
    assert(solve("ab+c.aba.*.bac.+.+*", 3, 2)=="YES");
    assert(solve("acb..bab.c.*.ab.ba.+.+*a.", 3, 0)=="NO");
    assert(solve("acb..bab.c.*.ab.ba.+.+*a.", 0, 1)=="ERROR");
    assert(solve("acb..bab.c.*.ab.ba.+.+*a.", 1, 0)=="YES");

    assert(solve("aaaaa...",5,5)=="ERROR");
    assert(solve("a+",5,5)=="ERROR");
    assert(solve("a.",5,5)=="ERROR");
    assert(solve("a*",5,5)=="YES");
    for(int k=1; k < 100; ++k) for(int l=0; l < k; ++l) assert(solve("a*",k,l)=="YES");
    for(int k=1; k < 100; ++k) for(int l=0; l < k; ++l)
        if(k%5!=0 || l%5==0) assert(solve("aaaaa....*",k,l)=="YES");
        else assert(solve("aaaaa....*",k,l)=="NO");

    for(int k=1; k < 100; ++k) for(int l=0; l < k; ++l)
            if(l<6) assert(solve("1a+aa.+aaa..+aaaa...+aaaaa....+",k,l)=="YES");
            else assert(solve("1a+aa.+aaa..+aaaa...+aaaaa....+",k,l)=="NO");

    for(int k=1; k < 100; ++k) for(int l=0; l < k; ++l)
            assert(solve("aaaa...aaaaa....+*",k,l)=="YES");


    for(int k=1; k < 100; ++k) for(int l=0; l < k; ++l)
            if(l<6) assert(solve("1a+aa.+aaa..+aaaa...+aaaaa....+",k,l)=="YES");
            else assert(solve("1a+aa.+aaa..+aaaa...+aaaaa....+",k,l)=="NO");

    std::vector<std::string> testStrings = {"a", "bc+*", "1abc.++", "acc.+", "aaa..*bc.*+", "1a.1a+."};
    int sz = testStrings.size();
    for(int i=0;i<sz;++i) for(int j=0;j<sz;++j) testStrings.push_back(testStrings[i]+testStrings[j]+'+');
    for(int i=0;i<sz;++i) for(int j=0;j<sz;++j) testStrings.push_back(testStrings[i]+testStrings[j]+'.');
    for(int i=0;i<3*sz;++i) testStrings.push_back(testStrings[i]+'*');
    for(auto s:testStrings) for(int k=1; k < 9; ++k) for(int l=0; l < k; ++l) {
        assert(solve(s, k, l) == solve(s+"1.", k, l));
        assert(solve(s+'*', k, l) == solve(s+"**", k, l));
        assert(solve(s+"a+", k, l) == solve(s+"a+b+", k, l));
        assert(solve(s+testStrings.back()+'.', k, l) == solve(testStrings.back()+s+'.', k, l));
    }
};