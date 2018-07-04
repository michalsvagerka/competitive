#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<998244353> FF;

class TaskD {
public:
    vector<int> N;
    int K;
    vector<vector<vector<int>>> E;

    void solve(istream& cin, ostream& cout) {
        N.resize(2);
        cin >> N[0] >> N[1] >> K;
        E.resize(2);
        if (K%2) { cout << 0 << endl; return; }
        K /= 2;

        vector2<unordered_map<pii, FF>> D(2, K+1), R(2, K+1);
        for (int j = 0; j < 2; ++j) {
            E[j].resize(N[j]);
            for (int i = 0; i < N[j]-1; ++i) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                E[j][u].push_back(v);
                E[j][v].push_back(u);
            }

            for (int u = 0; u < N[j]; ++u) {
                D[j][0][{u,-1}] = FF{1};
                R[j][0][{u,-1}] = FF{1};
                for (int v:E[j][u]) {
                    D[j][0][{u,v}] = FF{1};
                    R[j][0][{u,v}] = FF{1};
                }
            }

            for (int k = 1; k <= K; k++) {
                for (int u = 0; u < N[j]; ++u) {
                    for (int v:E[j][u]) {
                        D[j][k][{u,-1}] += R[j][k-1][{v,u}];
                    }
                    R[j][k][{u,-1}] = D[j][k][{u,-1}];

                    for (int v:E[j][u]) {
                        D[j][k][{u,v}] = D[j][k][{u,-1}] - R[j][k-1][{v,u}];
                        R[j][k][{u,v}] = D[j][k][{u,v}];
                    }

                    for (int l = 1; l <= k-1; ++l) {
                        for (int v:E[j][u]) { R[j][k][{u,v}] += D[j][l][{u,v}] * R[j][k-l][{u,v}]; }
                        R[j][k][{u,-1}] += D[j][l][{u,-1}] * R[j][k-l][{u,-1}];
                    }
                }
            }
        }

        auto F = FF::fact(2*K);
        auto I = FF::invfact(2*K);

        vector2<FF> Z(2, K+1, 0);
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k <= K; ++k) {
                for (int u = 0; u < N[j]; ++u) {
                    Z[j][k] += R[j][k][{u,-1}];
                }
            }
        }


        FF ans = 0;
        for (int d = 0; d <= K; ++d) {
            ans += Z[0][d] * Z[1][K-d] * F[2*K] * I[2*d] * I[2*(K-d)];
        }
        cout << ans << endl;
    }
};
