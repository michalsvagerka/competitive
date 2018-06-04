#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        vector<int> S(16); cin >> S;
        int ans = 0;
        for (int i = 0; i < 16; ++i) {
            if (S[i] > S[3] - 300) ++ans;
        }
        cout << ans << endl;
    }
};
