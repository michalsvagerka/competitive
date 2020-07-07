#include "../../../l/lib.h"
#include "../../../l/graph.h"

class GTwoPaths {
public:
    int N, Q;
    vector<int> A;
    vector<vector<pii>> E;
    TreeX T{1};
    vector<ll> Down, AllChildren, DownSum, FromUp, Siblings, Sum;

    void down(int u, int p, int c) {
        ll cc = 0;
        for (pii v : E[u]) {
            if (v.x != p) {
                down(v.x, u, v.y);
                cc += Down[v.x];
            }
        }

        AllChildren[u] = cc;
        for (pii v: E[u]) {
            if (v.x != p) {
                Siblings[v.x] = cc - Down[v.x];
            }
        }
        cc += A[u] - 2*c;
        Down[u] = max(0LL, cc);
    }

    void prop(int u, int p, ll tot, ll up) {
        Sum[u] = tot + AllChildren[u];
        FromUp[u] = up + A[u] - 2 * tot - AllChildren[u];
        for (pii v : E[u]) {
            if (v.x != p) {
                prop(v.x, u, tot - v.y + A[v.x] + Siblings[v.x], max(0LL, up + A[u] - 2 * v.y + AllChildren[u] - Down[v.x]));
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> Q;
        A.resize(N); cin >> A;
        E.resize(N);
        T = TreeX(N);
        Down.resize(N);
        Sum.resize(N);
        FromUp.resize(N);
        Siblings.resize(N);
        AllChildren.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v, w; cin >> u >> v >> w;
            --u; --v;
            E[u].emplace_back(v,w);
            E[v].emplace_back(u,w);
            T.addEdge(u, v);
        }
        T.calcLA();

        Siblings[0] = 0;
        down(0, -1, 0);
        prop(0, -1, A[0] + Siblings[0], 0);

        for (int q = 0; q < Q; ++q) {
            int a, b; cin >> a >> b;
            --a; --b;
            int c = T.lca(a, b);
            cout << Sum[a] + Sum[b] + FromUp[c] << '\n';
        }
    }
};
