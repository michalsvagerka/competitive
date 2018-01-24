#include "../l/lib.h"
// #include "../l/mod.h"

int q = 62;
class t2vazenestromy2 {
public:
    ui uptok(ll k) {
        ui ans = 0;
        for (int i = q-1; i >= 0; --i) {
            ll b = 1LL<<i;
            if (k&b) {
                k^=b;
                ans += W[i] + T[i] * k;
            }
        }
        return ans;
    }

    vector<ui> D,T,Z,W;

    void solve(istream& cin, ostream& cout) {
        Z.resize(q);
        T.resize(q);
        D.resize(q);
        W.resize(q);
        Z[0] = W[0] = 0; T[0] = D[0] = 1;
        for (int i = 1; i < q; ++i) {
            D[i] = D[i-1] * 2;
            T[i] = T[i-1] * 3;
            Z[i] = Z[i-1] + T[i-1];
            W[i] = Z[i] * D[i-1];
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll l,r; cin >> l >> r;
            cout << uptok(r+1) - uptok(l) << '\n';
        }
    }
};
