#include "../../../l/lib.h"
// #include "../l/mod.h"

class fish {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<double> A(N,N); cin >> A;
        vector<double> P(1<<N, 0);
        P[(1<<N)-1] = 1;
        for (int i = (1<<N)-1; i > 0; --i) {
            int s = __builtin_popcount(i);
            int t = s*(s-1)/2;
            for (int j = 0; j < N; ++j) {
                if (i&(1<<j)) {
                    for (int k = j + 1; k < N; ++k) {
                        if (i&(1<<k)) {
                            P[i^(1<<k)] += P[i]*A[j][k]/t;
                            P[i^(1<<j)] += P[i]*A[k][j]/t;
                        }
                    }
                }
            }
        }

        vector<double> E(N);
        for (int i = 0; i < N; ++i) {
            E[i] = P[1<<i];
        }
        cout << fixed << setprecision(10) << E;
    }
};
