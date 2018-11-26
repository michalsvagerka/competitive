#include "../l/lib.h"
// #include "../l/mod.h"

class pocettestov {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        string mn(S[0].size(), '0');
        mn[0] = '1';
        for (string s: S) mn = max(mn, s);
        string mx(S[0].size(), '9');

        cout << mn << '\n' << mx << '\n';
    }
};
