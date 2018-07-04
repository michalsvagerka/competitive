#include "../l/lib.h"
 #include "../l/mod.h"
#include "../l/graph.h"

class TaskD {
public:

    void solve(istream& cin, ostream& cout) {
        int N, K;
        vector<vector<int>> E;
        Tree T;

        cin >> N >> K;
        T = Tree(N);
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
            T.addEdge(u,v);
        }

        T.calcLA();

        int ans = 1;
        int r = 0, cur = 0;
        vector<bool> Present(N, false);
        vector<unordered_set<int>> Edges(N);
        Present[0] = true;

        for (int l = 0; l < N; ++l) {
            while (r < N && cur <= K) {
                ans = max(ans, r-l);

                // add "r"
                if (l == r) {
                    Present[r] = true;
                    r++;
                    cur++;
                    continue;
                }

                int lca = T.lca(r-1, r);
                if (T.depth(r-1) + T.depth(r) - 2*T.depth(lca) + 1 > K) break;

                int s = r;
                while (s != lca && !Present[s]) {
                    Present[s] = true;
                    cur++;

                    Edges[s].insert(T.parent(s));
                    Edges[T.parent(s)].insert(s);

                    s = T.parent(s);
                }

                int d = T.depth(l) - T.depth(lca);
                int v = lca;
                for (int i = d; !Present[v] && i > 0; --i) {
                    int w = T.la(l, i-1);
                    Present[v] = true;
                    cur++;
                    Edges[v].insert(w);
                    Edges[w].insert(v);

                    v = w;
                }

                r++;
            }

            if (cur <= K) ans = max(ans, r-l);

            // remove "l"
            int g = l;
            while (Edges[g].size() <= 1) {
                if (Edges[g].empty()) {
                    Present[g] = false;
                    cur = 0;
                    break;
                }
                int w = *(Edges[g].begin());
                Edges[g].clear();
                Edges[w].erase(g);
                Present[g] = false;
                g = w;
                --cur;
                if (g > l && g < r) break;
            }
        }
        cout << ans << endl;
    }
};
