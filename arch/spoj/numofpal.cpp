#include "../../l/lib.h"
// #include "../l/mod.h"

class numofpal {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        cin >> S;
        Eertree<char> T;
        for (char s : S) {
            T.insertChar(s);
        }
//        T.print(cout);
        ll ans = 0;
        for (int i = 2; i < T.V.size(); ++i) {
            ans += (ll)T.V[i].chain * T.V[i].count;
        }
        cout << ans << endl;
    }
};
