#include "../l/lib.h"
#include "../l/hungary.h"

const int inf = 1000000;

class omrvinky {
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

        int q = N;
        for (int i = 0; i < N; ++i) {
            q -= C[i]%2;
            for (int j = 0; j < N; ++j) {
                if (i == j) D[i][j] = inf;
                else if (C[i]%2==0||C[j]%2==0) D[i][j] = inf;
            }
        }

        Hungary<int> H(D);
        cout << ans+(H.minCost() - q*inf)/2 << endl;
    }
};
