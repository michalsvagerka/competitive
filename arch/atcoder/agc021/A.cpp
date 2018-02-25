#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        if (count(S.begin()+1,S.end(),'9') == S.size() - 1) {
            cout << 9*(S.size()-1) + (S[0]-'0') << endl;
        } else {
            cout << 9*(S.size()-1) + (S[0]-'1') << endl;
        }
    }
};
