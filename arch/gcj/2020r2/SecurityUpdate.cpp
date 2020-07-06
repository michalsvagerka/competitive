#include "../l/lib.h"

class SecurityUpdate {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            vector<int> V(N-1); cin >> V;
            vector<vector<int>> E(N);
            vector<pii> F;
            for (int i = 0; i < M; ++i) {
                int u, v; cin >> u >> v;
                --u; --v;
                E[u].push_back(v);
                E[v].push_back(u);
                F.push_back({u,v});
            }

            vector<pii> Known;
            vector<pii> Count;
            Known.push_back({0,0});
            for (int i = 0; i < N-1; ++i) {
                if (V[i] < 0) {
                    Count.push_back({-V[i],i+1});
                } else {
                    Known.push_back({V[i],i+1});
                }
            }

            sort(Count.begin(),Count.end());
            sort(Known.begin(),Known.end());
            vector<pii> Sort(N);
            int j = 0, k = 0;
            for (int i = 0; i < N; ++i) {
                if (j < Count.size() && Count[j].x <= i) {
                    Sort[i] = {Count[j].y, Sort[Count[j].x-1].y+1};
                    ++j;
                } else {
                    Sort[i] = {Known[k].y, Known[k].x};
                    ++k;
                }
            }
            vector<int> Dist(N);
            for (int i = 0; i < N; ++i) {
                Dist[Sort[i].x] = Sort[i].y;
            }

            cout << "Case #" << t+1 << ":";
            for (pii f: F) {
                cout << ' ' << max(1, abs(Dist[f.x]-Dist[f.y]));
            }
            cout << '\n';
        }
    }
};
