#include "../../../l/lib.h"
#include "../../../l/util.h"

class limakandsquaregrid {
public:
    void solve(istream& cin, ostream& cout) {
        int K, N; cin >> N >> K;
        if (K == N) {
            cout << K*K << endl;
            return;
        }

        vector<string> S(N); cin >> S;
        UnionFind UF(N*N);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (S[r][c] == 'X') continue;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr*dc==0 && dr+dc!=0) {
                            int rr = r+dr, cc = c+dc;
                            if (in(0,rr,N) && in(0,cc,N) && S[rr][cc] == '.') {
                                UF.unite(r*N + c, rr*N + cc);
                            }
                        }
                    }
                }
            }
        }

        vector2<int> P(N+1,N+1,0), R(N+1,N+1,0), W(N,N);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                P[r+1][c+1] = P[r+1][c] + P[r][c+1] - P[r][c] + (S[r][c] == '.');
                R[r+1][c+1] = R[r+1][c] + R[r][c+1] - R[r][c] + (S[r][c] == '.'?max(0,-UF.P[r*N+c]) : 0);
                W[r][c] = UF.find(r*N+c);
            }
        }

        int tot = 0;
        vector<int> L(N*N, -1);
        int k = 0;
        for (int t = 0; t + K <= N; ++t) {
            for (int l = 0; l + K <= N; ++l) {
                int origins = R[t+K][l+K] - R[t+K][l] - R[t][l+K] + R[t][l];
                int inner = P[t+K][l+K] - P[t+K][l] - P[t][l+K] + P[t][l];
                int ans = K*K + origins - inner;

                vector<int> Z;
                if (t != 0) for (int c = l; c < l + K; ++c) if (S[t-1][c] == '.' && L[W[t-1][c]] < k) { L[W[t-1][c]] = k; Z.push_back(W[t-1][c]); }
                if (t+K != N) for (int c = l; c < l + K; ++c) if (S[t+K][c] == '.' && L[W[t+K][c]] < k) { L[W[t+K][c]] = k; Z.push_back(W[t+K][c]); }
                if (l != 0) for (int r = t; r < t + K; ++r) if (S[r][l-1] == '.' && L[W[r][l-1]] < k) { L[W[r][l-1]] = k; Z.push_back(W[r][l-1]); }
                if (l+K != N) for (int r = t; r < t + K; ++r) if (S[r][l+K] == '.' && L[W[r][l+K]] < k) { L[W[r][l+K]] = k; Z.push_back(W[r][l+K]); }

                for (int z:Z) {
                    int size = -UF.P[z], r = z/N, c = z%N;
                    bool inside = in(t,r,t+K) && in(l,c,l+K);
                    if (!inside) ans += size;
                }

                int cur = ans;
                tot = max(tot, cur);
                ++k;
            }
        }

        cout << tot << endl;

    }
};
