#include "../l/lib.h"
 #include "../l/util.h"

class civilization {
public:
    vector<vector<int>> E;

    pii diam(int u, int p) {
        pii x = {-1,u};
        for (int v:E[u]) {
            if (v != p) {
                x = max(x, diam(v, u));
            }
        }
        x.x++;
        return x;
    }

    void solve(istream& cin, ostream& cout) {
        int N, M, Q; cin >> N >> M >> Q;
        E.resize(N);
        UnionFind U(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
            U.unite(u,v);
        }

        vector<int> D(N, 0);
        for (int i = 0; i < N; ++i) {
            if (U.find(i) == i) {
                pii r = diam(i, -1);
                D[i] = diam(r.y, -1).x;
            }
        }

        for (int q = 0; q < Q; ++q) {
            int t; cin >> t;
            if (t == 2) {
                int a,b; cin >> a >> b;
                --a; --b;
                a = U.find(a);
                b = U.find(b);
                if (a != b) {
                    int d = max(max(D[a], D[b]), (D[a]+1)/2 + (D[b]+1)/ 2 + 1);
                    U.unite(a,b);
                    D[U.find(a)] = d;
                }
            } else {
                int x; cin >> x; --x;
                x = U.find(x);
                cout << D[x] << '\n';
            }
        }

    }
};
