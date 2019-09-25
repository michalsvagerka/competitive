#include "../l/lib.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            if (M < N-1) {
                cout << "-" << endl;
                continue;
            }
            vector<int> Degree(N, 0);
            vector<vector<int>> Components(N);
            vector<int> Component(N);
            vector<int> Comsize(N, 1);
            vector<set<pii>> VertexByDegree(N); // compId -> list(degree * vertex Id)
            set<pii> CompsBySize; // (compsize * compId)
            for (int i = 0; i < N; ++i) {
                Components[i].push_back(i);
                VertexByDegree[i].insert({0, i});
                CompsBySize.insert({1, i});
                Component[i] = i;
            }

            while (CompsBySize.size() > 1) {
                auto c = *CompsBySize.begin();
                if (VertexByDegree[c.y].empty()) break;
                auto v = *VertexByDegree[c.y].rbegin();
                VertexByDegree[c.y].erase(v);
                cout << "? " << v.y+1 << endl;
                int j; cin >> j;
                if (j == -1) {
                } else {
                    --j;
                    int k = v.y;
                    int a = Component[j], b = Component[k];

                    VertexByDegree[Component[j]].erase({Degree[j], j});
                    Degree[j]++;
                    Degree[k]++;

                    if (a != b) {
                        if (Comsize[a] > Comsize[b]) swap(a, b);
                        CompsBySize.erase({Comsize[a], a});
                        CompsBySize.erase({Comsize[b], b});

                        // add all a to b
                        for (pii vbd: VertexByDegree[a]) {
                            VertexByDegree[b].insert(vbd);
                        }

                        for (int i: Components[a]) {
                            Components[b].push_back(i);
                            Component[i] = b;
                        }
                        Components[a].clear();

                        Comsize[b] += Comsize[a];
                        Comsize[a] = 0;
                        CompsBySize.insert({Comsize[b], b});
                        VertexByDegree[a].clear();
                    }
                    VertexByDegree[Component[j]].insert({Degree[j], j});
                    VertexByDegree[Component[k]].insert({Degree[k], k});
                }
            }

            cout << "-+"[CompsBySize.size() == 1] << endl;
        }
    }
};
