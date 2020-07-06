#include "../l/lib.h"
#include "../l/graph.h"
#include "../l/nsegtree.h"

constexpr int X = 200;
constexpr int MX = 20000;
class saharatravel {
public:
    int N, Q;
    vector<vector<pii>> E;
    vector<int> Enter, Exit, Ans;
    vector<vector<pair<pii, int>>> Queries;
    void solve(istream& cin, ostream& cout) {
        cin >> N >> Q;
        E.resize(N);
        Ans.resize(Q);
        for (int i = 0; i < N - 1; ++i) {
            int a, b, c; cin >> a >> b >> c;
            --a; --b;
            E[a].push_back({b,c});
            E[b].push_back({a,c});
        }


        DFSOrder<pii> D(E);
        Enter = D.enter();
        Exit = D.exit();
        E = D.linearize();

        Queries.resize(MX+1);
        for (int q = 0; q < Q; ++q) {
            int s,f,d; cin >> s >> f >> d;
            Queries[d].push_back({{Enter[s-1],Enter[f-1]},q});
        }

        DFSOrder<pii> D2(E);
        Enter = D2.enter();
        Exit = D2.exit();

        TreeX T(N);
        for (int i = 0; i < N; ++i) for (pii e: E[i]) if (e.x < i) T.addEdge(e.x, i);
        T.calcLA();

        for (int di = 1; di <= X; ++di) {
            if (Queries[di].empty()) continue;

            vector<int> X(N, 0);
            for (int i = 0; i < N; ++i) {
                for (pii j: E[i]) if (j.x > i) {
                    X[j.x] = X[i] + (j.y-1)/di + 1;
                }
            }

            for (auto query: Queries[di]) {
                int u = query.x.x;
                int v = query.x.y;
                Ans[query.y] = X[u] + X[v] - 2*X[T.lca(u, v)] + 1;
            }
        }

        constexpr int QUERY = 0;
        constexpr int EDGE = 1;
        vector<vector<pair<pii, pii>>> Events(MX+1);
        for (int i = 0; i < N; ++i) {
            for (pii j: E[i]) {
                if (j.x < i) {
                    Events[j.y].push_back({{EDGE, -1}, {i,j.x}});
                }
            }
        }

        for (int di = X+1; di <= MX; ++di) {
            for (auto query: Queries[di]) {
                int u = query.x.x;
                int v = query.x.y;
                int l = T.lca(u,v);
                Ans[query.y] = T.depth(u) + T.depth(v) - 2*T.depth(l) + 1;
                for (int x = di; x <= MX; x += di) {
                    Events[x].push_back({{QUERY, query.y}, {u, 1}});
                    Events[x].push_back({{QUERY, query.y}, {v, 1}});
                    Events[x].push_back({{QUERY, query.y}, {l, -2}});
                }
            }
        }

        AddSumTree<int> Seg(N, 0, 0);
        for (int c = MX; c > X; --c) {
            sort(Events[c].begin(),Events[c].end());
            for (auto event: Events[c]) {
                if (event.x.x == QUERY) {
                    Ans[event.x.y] += event.y.y * Seg.get(event.y.x);
                } else {
                    int u = event.y.x;
                    Seg.put(Enter[u], Exit[u]-1, 1);
                }
            }
        }

        for (int ans: Ans) cout << ans << '\n';
    }
};
