#include "../l/lib.h"
// #include "../l/mod.h"

class tridrom {
public:
    void solve(istream& cin, ostream& cout) {
        string s;
        getline(cin,s);
        ll ans = 0;
        vector<ll> T(128, 0), L(128, 0);
        for (char c:s) {
            if (c != ' ') {
                ans += L[c];
                for (int i = 65; i < 128; ++i) L[i] += T[i];
                T[c]++;
            }
        }
        cout << ans << endl;
    }
};
