#include "../l/lib.h"
#include <cstring>

int DP[10000][1001];

class CGuest {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> D(M); cin >> D;
        int G, R; cin >> G >> R;
        sort(D.begin(),D.end());
        for (int i = 0; i < M; ++i) {
            fill(DP[i], DP[i]+G+1, 2*M);
        }
        DP[0][0] = 0;
        int dist = 0;
        vector<pii> Q{{0,0}};
        while (!Q.empty()) {
            vector<pii> W;
            for (int q = 0; q < Q.size(); ++q) {
                pii a = Q[q];
                if (a.y == G) {
                    DP[a.x][0] = DP[a.x][G]+1;
                    W.push_back({a.x,0});
                }
                if (a.x != 0) {
                    int l = a.y + (D[a.x]-D[a.x-1]);
                    if (l <= G && DP[a.x-1][l] > M) {
                        DP[a.x-1][l] = DP[a.x][a.y];
                        Q.emplace_back(a.x-1,l);
                    }
                }
                if (a.x != M-1) {
                    int l = a.y + (D[a.x+1]-D[a.x]);
                    if (l <= G && DP[a.x+1][l] > M) {
                        DP[a.x+1][l] = DP[a.x][a.y];
                        Q.emplace_back(a.x+1,l);
                    }
                }
            }

            swap(W,Q);
        }

        int ans = 1e9;
        for (int i = 0; i <= G; ++i) ans = min(ans, (R+G)*DP[M-1][i] + i);
        cout << (ans < 2*(R+G)*M ? ans : -1) << '\n';
    }
};
