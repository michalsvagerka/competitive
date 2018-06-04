#include "../../../l/lib.h"
#include "../../../l/graph.h"
// #include "../l/mod.h"

class farebnyokruh {
public:

    vector2<map<int, set<int>>> Edges;
    vector<pair<pii, int>> E;

    void removeEdge(int z, int id, int c) {
        int u = E[id].x.x-1;
        int v = E[id].x.y-1;
        if (z) swap(u,v);

        Edges[z][u][c].erase(id);
        Edges[!z][v][c].erase(id);
        bool reduceU = Edges[z][u][c].empty();
        bool reduceV = Edges[!z][v][c].empty();
        if (reduceU) Edges[z][u].erase(c);
        if (reduceV) Edges[!z][v].erase(c);
        if (reduceU && Edges[z][u].size() <= 1) fix(u);
        if (reduceV && Edges[!z][v].size() <= 1) fix(v);
    }

    void fix(int v) {
        for (int z = 0; z < 2; ++z) {
            if (Edges[z][v].empty()) {
                while (!Edges[!z][v].empty()) {
                    int c = Edges[!z][v].begin()->x;
                    while (!Edges[!z][v][c].empty()) {
                        removeEdge(!z, *Edges[!z][v][c].begin(), c);
                    }
                    Edges[!z][v].erase(c);
                }
            } else if (Edges[z][v].size() == 1) {
                int c = Edges[z][v].begin()->x;
                if (Edges[!z][v].find(c) == Edges[!z][v].end()) continue;

                while (!Edges[!z][v][c].empty()) {
                    removeEdge(!z, *Edges[!z][v][c].begin(), c);
                }
                Edges[!z][v].erase(c);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            E.resize(M); cin >> E;
            map<pii, vector<int>> Z;

            DirectedGraph DG(N);
            for (int i = 0; i < M; ++i) {
                DG.addEdge(E[i].x.x-1, E[i].x.y-1);
                Z[{E[i].x.x-1,E[i].x.y-1}].push_back(i);
            }
            DG.calcStronglyConnectedComponents();

            Edges.clear();
            Edges.resize(2);
            Edges[0].resize(N);
            Edges[1].resize(N);
            for (int u = 0; u < N; ++u) {
                for (int v:DG.E[u]) {
                    if (DG.SCC[u] == DG.SCC[v]) {
                        for (int i:Z[{u,v}]) {
                            Edges[0][u][E[i].y].insert(i);
                            Edges[1][v][E[i].y].insert(i);
                        }
                    }
                }
            }

            for (int u = 0; u < N; ++u) {
                for (int z = 0; z < 2; ++z) {
                    if (Edges[z][u].size() <= 1) fix(u);
                }
            }

            bool found = false;
            for (int u = 0; u < N; ++u) {
                if (!Edges[0][u].empty()) {
                    int c = 0;
                    map<int, int> Pos;
                    vector<int> Ids;

                    bool pathEnd = false;
                    while (!pathEnd) {
                        for (auto & edgeList : Edges[0][u]) {
                            if (edgeList.x == c) continue;
                            int edge = *edgeList.y.begin();
                            Ids.push_back(edge);
                            c = E[edge].y;
                            u = E[edge].x.y-1;
                            if (Pos[edge] > 0) {
                                pathEnd = true;
                            } else {
                                Pos[edge] = Ids.size();
                            }
                            break;
                        }
                    }

                    found = true;
                    cout << Ids.size() - Pos[Ids.back()] << '\n';
                    for (int i = Pos[Ids.back()]; i < Ids.size(); ++i) {
                        cout << Ids[i]+1 << " \n"[i==Ids.size()-1];
                    }
                    break;
                }
            }

            if (!found) {
                cout << "-1\n";
            }
        }
    }
};
