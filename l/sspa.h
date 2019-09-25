#ifndef SSPA_MAXFLOW
#define SSPA_MAXFLOW
#include "lib.h"

/** Successive shortest paths algorithm.
 * If linearDijkstra is true, runs in O(maxFlow * (|E| + sumCosts)).
 * Otherwise, runs in O(maxFlow * |E| * log |E|). */
template<typename Cap = int, typename Cost = int, bool linearDijkstra = false>
struct SSPA {
    struct Edge{
        Cost c; Cap f; int to, rev;
        Edge(int _to, Cost _c, Cap _f, int _rev):c(_c), f(_f), to(_to), rev(_rev){}
    };
    int N, source, sink;
    vector<vector<Edge>> G;
    SSPA(int N, int source, int sink): N(N), source(source), sink(sink), G(N) {}
    void addEdge(int a, int b, Cap cap, Cost cost) {
        assert(cap>=0);
        assert(a>=0&&a<N&&b>=0&&b<N);
        if(a==b){assert(cost>=0); return;}
        G[a].emplace_back(b, cost, cap, G[b].size());
        G[b].emplace_back(a, -cost, 0, G[a].size()-1);
    }

    pair<Cap, Cost> minCostMaxFlow() {
        /* Vertex potentials. These are maintained so that all edges with non-zero
         * residual have non-negative length. Thus, Dijkstra can be used instead of
         * Bellman-Ford in each step of the algorithm. */
        vector<Cost> Pi(N, 0);
        Cost infty = std::numeric_limits<Cost>::max();
        Cap totFlow = 0;
        Cost totCost = 0;
        while (true) {
            vector<Cost> D(N, infty);
            vector<int> Prev(N, -1);
            D[source] = 0;

            if (linearDijkstra) {
                vector<vector<int>> Q{{source}};
                for (int i = 0; i < Q.size(); ++i) {
                    for (int j = 0; j < Q[i].size(); ++j) {
                        int u = Q[i][j];
                        if (D[u] < i) continue;

                        for (auto &e: G[u]) {
                            if (e.f > 0) {
                                cerr << e.c << endl;
                                Cost c = D[u] + e.c;
                                if (D[e.to] > c) {
                                    D[e.to] = c;
                                    while (c >= Q.size()) Q.emplace_back();
                                    Q[c].push_back(e.to);
                                    Prev[e.to] = u;
                                }
                            }
                        }
                    }
                }
            } else {
                minheap<pair<Cost, int>> Q;
                Q.push({0,source});
                while (!Q.empty()) {
                    auto q = Q.top(); Q.pop();
                    int u = q.y;
                    if (D[u] < q.x) continue;

                    for (auto &e: G[u]) {
                        if (e.f > 0) {
                            Cost c = D[u] + e.c;
                            if (D[e.to] > c) {
                                D[e.to] = c;
                                Q.push({c, e.to});
                                Prev[e.to] = u;
                            }
                        }
                    }
                }
            }

            cerr << D << Pi;

            // if sink is unreachable, flow is optimal
            if (D[sink] == infty) break;

            // reconstruct some shortest path
            int w = sink;
            vector<int> Path;
            while (w != -1) { Path.push_back(w); w = Prev[w]; }
            reverse(Path.begin(),Path.end());

            // found the minimum of the edge residuals along the path
            Cap augment = std::numeric_limits<Cap>::max();
            int L = Path.size();
            for (int i = 0; i < L-1; ++i) {
                int u = Path[i], v = Path[i+1];
                for (auto&e: G[u]) {
                    // be careful, there might be multiedges
                    if (e.to == v && e.f > 0 && D[v] == D[u] + e.c) {
                        augment = min(augment, e.f);
                        break;
                    }
                }
            }

            for (int i = 0; i < L-1; ++i) {
                int u = Path[i], v = Path[i+1];
                for (auto&e: G[u]) {
                    if (e.to == v && e.f > 0 && D[v] == D[u] + e.c) {
                        e.f -= augment;
                        G[v][e.rev].f += augment;
                        break;
                    }
                }
            }

            // store the cost & flow size
            Cost cost = Pi[source] - Pi[sink] + D[sink];
            totFlow += augment;
            totCost += cost * augment;

            // remove potentials from costs
            for (int i = 0; i < N; ++i) {
                for (auto &e: G[i]) {
                    e.c -= Pi[e.to] - Pi[i];
                }
            }


            // add potentials to costs again
            for (int i = 0; i < N; ++i) {
                for (auto &e: G[i]) {
                    e.c += (Pi[e.to] - D[e.to]) - (Pi[i] - D[i]);
                }
            }

            // update potentials based on the results
            for (int i = 0; i < N; ++i) Pi[i] -= D[i];

        }
        return {totFlow,totCost};
    }
};
#endif