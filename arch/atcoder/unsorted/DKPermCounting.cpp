#include "../l/lib.h"
 #include "../l/mod.h"
#include <numeric>

typedef Field<924844033> FF;
auto F = FF::fact(10000);
auto I = FF::invfact(10000);

class DKPermCounting {
public:
    vector<FF> CNT;


    void single(int N) {
        vector3<FF> Z(N+1, 2, 2, 0);
        Z[0][0][0] = 1;
        for (int i = 0; i < N; ++i) {
            vector3<FF> W(N+1, 2, 2, 0);

            for (int j = 0; j <= i; ++j) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        auto z = Z[j][k][l];
                        W[j][l][0] += z;
                        if (i!=N-1) W[j+1][l][1] += z;
                        if (k!=1 && i!=0) W[j+1][l][0] += z;
                    }
                }
            }
            swap(W, Z);
        }

        CNT.assign(N+1, 0);
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    CNT[i] += Z[i][j][k];
                }
            }
        }
    }


    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;

        if (N%K != 0) single(N/K+1);
        vector<FF> Z{1};
        for (int i = 0; i < K; ++i) {
            int tot = Z.size();
            int cur = N/K + (i<N%K);

            if (i == N%K) single(N/K);
            vector<FF> H(tot + cur, 0);
            for (int j = 0; j < tot; ++j) {
                for (int k = 0; k <= cur; ++k) {
                    H[j+k] += Z[j] * CNT[k];
                }
            }
            swap(H,Z);
        }

        for (int i = 0; i <= N; ++i) {
            Z[i] *= F[N-i];
        }

        vector<FF> W(N+1, 0);
        for (int i = 0; i <= N; ++i) {
            for (int j = i; j <= N; ++j) {
                FF a = Z[j] * F[j] * I[i] * I[j-i];
                if ((j-i)%2) W[i] -= a; else W[i] += a;
            }
        }
        cout << W[0] << '\n';
    }
};
