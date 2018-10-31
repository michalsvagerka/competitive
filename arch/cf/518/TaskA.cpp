#include "../l/lib.h"
 #include "../l/mod.h"
typedef Field<998244353> F;

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;

    int mx = 200;
    vector2<F> G(2, mx+1, 0);
    G[1][0] = 1;
    for (int i = 0; i < N; ++i) {
        vector2<F> H(2, mx+1, 0);
        if (A[i] > 0) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k <= mx; ++k) {
                    if (j == 0 && A[i] < k) break;
                    H[A[i] <= k][A[i]] += G[j][k];
                }
            }
        } else {
            F t = G[0][0];
            for (int i = 1; i <= mx; ++i) {
                H[0][i] += t;
                t += G[0][i];
                H[1][i] = G[0][i];
            }

            F s = G[1][0];
            for (int i = 1; i <= mx; ++i) {
                H[0][i] += s;
                s += G[1][i];
            }

            F g = 0;
            for (int i = mx; i >= 1; --i) {
                g += G[1][i];
                H[1][i] += g;
            }
        }

        swap(G, H);
//        cout << G;
    }

    F ans = 0;
    for (int i = 0; i <= mx; ++i) {
        ans += G[1][i];
    }
    cout << ans << endl;
}
};

