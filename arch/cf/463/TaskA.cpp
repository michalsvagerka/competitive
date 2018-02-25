#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        cin >> S;
        string T = S;
        reverse(T.begin(),T.end());
        cout << S << T << endl;
    }
};
