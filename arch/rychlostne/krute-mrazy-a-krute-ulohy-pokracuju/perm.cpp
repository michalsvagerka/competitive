#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<2147483647> T;

class perm {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        auto F = T::fact(200);
        auto I = T::invfact(200);
        vector<map<int,T>> R(N+1);
        R[0][1] = 1;
        for (int j = 1; j <= N; ++j) {
            for (int i = N-1; i >= 0; --i) {
                for (auto &r: R[i]) {
                    T z = 1;
                    ll q = (ll) r.x * j / gcd(r.x, j);
                    if (K % q == 0) {
                        for (int k = 1; k * j + i <= N; ++k) {
                            z *= F[N - i - (k-1)*j] * I[N - i - k*j] / j;
                            R[i + k * j][(int) q] += r.y * z * I[k];
                        }
                    }
                }
            }
        }
        cout << R[N][K] << endl;
    }
};
