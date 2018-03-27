#include "../../../l/lib.h"
#include "../../../l/graph.h"

class TaskC {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, H; cin >> N >> M >> H;
        vector<int> U(N); cin >> U;
        DirectedGraph G(N);
        vector<unordered_set<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int c,d; cin >> c >> d;
            --c; --d;
            if ((U[c] + 1) % H == U[d]) {
                if (E[c].find(d) == E[c].end()) {
                    E[c].insert(d);
                    G.addEdge(c, d);
                }
            }
            if ((U[d] + 1) % H == U[c]) {
                if (E[d].find(c) == E[d].end()) {
                    E[d].insert(c);
                    G.addEdge(d, c);
                }
            }
        }

        vector<vector<int>> C(N);
        vector<int> R(N);
        for (int i = 0; i < N; ++i) {
            C[G.stronglyConnectedComponent(i)].push_back(i);
            R[i] = G.stronglyConnectedComponent(i);
        }

        int ans = -1, best = N+1;
        for (int i = 0; i < N; ++i) {
            if (!C[i].empty() && C[i].size() < best) {
                bool ok = true;
                for (int c:C[i]) {
                    for (int d:E[c]) {
                        if (R[c] != R[d]) {
                            ok = false;
                        }
                    }
                }
                if (ok) {
                    best = C[i].size();
                    ans = i;
                }
            }
        }

        for (int &c:C[ans]) ++c;
        cout << C[ans].size() << '\n';
        cout << C[ans];
    }
};
