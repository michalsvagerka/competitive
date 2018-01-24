#include "../l/lib.h"

const int inf = 1000000;

class omrvinky2 {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector2<int> D(N,N,inf);
        vector<int> C(N, 0);
        int ans = 0;
        for (int i = 0; i < M; ++i) {
            int a,b,c; cin >> a >> b >> c; --a; --b;
            D[a][b] = D[b][a] = min(c,D[b][a]);
            C[a]++;
            C[b]++;
            ans += c;
        }

        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                }
            }
        }

        int base = 0;
        for (int i = 0; i < N; ++i) {
            if (C[i]%2 == 0) base |= 1<<i;
        }

        vector<int> DP(1<<N, inf);
        DP[base] = 0;
        for (int i = 0; i < (1<<N); ++i) {
            if (DP[i]==inf) continue;
            for (int j = 0; j < N; ++j) {
                if (i&(1<<j)) continue;
                for (int k = j+1; k < N; ++k) {
                    if (i&(1<<k)) continue;
                    int m = i|(1<<j)|(1<<k);
                    DP[m] = min(DP[m], DP[i] + D[j][k]);
                }
            }
        }

        cout << ans + DP.back() << endl;
    }
};
