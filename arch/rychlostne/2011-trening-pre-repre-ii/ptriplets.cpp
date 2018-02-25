#include "../../../l/lib.h"
#include "../../../l/primes.h"
#include "../../../l/matrix.h"
#include "../../../l/mod.h"


typedef Field<1000000009> F;
int d[] = {1,3,7,9};

class ptriplets {
public:
    void solve(istream& cin, ostream& cout) {
        Sieve S(1000);
        F three = 0;
        for (int i = 100; i < 1000; ++i) three += F(S[i]);

        Matrix<F> M(16,16,0);
        for (int a = 0; a < 4; ++a) {
            for (int b = 0; b < 4; ++b) {
                for (int c = 0; c < 4; ++c) {
                    if (S[100*d[a] + 10*d[b] + d[c]]) M[4*b+c][4*a+b] = 1;
                }
            }
        }

        vector<Matrix<F>> Z{M};
        for (int i = 1; i < 60; ++i) Z.push_back(Z[i-1] * Z[i-1]);

        vector<F> B(16, 0);
        for (int a = 10; a < 100; ++a) {
            for (int b = 0; b < 4; ++b) {
                for (int c = 0; c < 4; ++c) {
                    if (S[10*a + d[b]] && S[(100*a)%1000 + 10*d[b] + d[c]]) {
                        B[4 * b + c] += 1;
                    }
                }
            }
        }


        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll N; cin >> N;
            if (N == 3) {
                cout << three << '\n';
            } else {
                N -= 4;
                vector<F> R = B;
                for (int i = 0; i < 60; ++i) if (N & (1LL<<i)) R = Z[i] * R;

                F res = 0;
                for (F r: R) res += r;
                cout << res << '\n';
            }
        }
    }
};
