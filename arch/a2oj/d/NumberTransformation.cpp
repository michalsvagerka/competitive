#include "../l/lib.h"
// #include "../l/mod.h"

class NumberTransformation {
public:
void solve(istream& cin, ostream& cout) {
    ll A, B; cin >> A >> B;
    int K; cin >> K;
    int g = 360360;
    ll C = A/g, D = B/g;
    ll ans = 0;
    for (int i = 0; i < 2; ++i) {
        int z = i ? B%g : 0;
        vector<int> S(g+1, 1e9);
        S[z] = 0;
        for (int j = z+1; j <= g; ++j) {
            S[j] = S[j-1] + 1;
            for (int k = 2; k <= K; ++k) {
                S[j] = min(S[j], S[j-j%k] + 1);
            }
        }

        if (i) {
            if (C == D) {
                ans += S[A%g];
            } else {
                ans += S[g];
            }
        } else {
            if (C > D) {
                ans += S[A%g];
                ans += (C-D-1) * S[g];
            }
        }
    }

    cout << ans << endl;

}
};
