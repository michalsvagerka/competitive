#include "../l/lib.h"
#include "../l/util.h"

constexpr int L = 18;

class paving {
public:


    vector<int> D;
    vector2<pii> P;
    vector<vector<pii>> G;

    void dfs(int u, int p, int c, int d) {
        P[0][u] = {p, c};
        D[u] = d;
        for (pii v:G[u]) {
            if (v.x != p) {
                dfs(v.x, u, v.y, d+1);
            }
        }
    }


void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<pair<int,pii>> F;
    unordered_map<pii, int> C;
    for (int i = 0; i < M; ++i) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        F.push_back({c,{a,b}});
        C[{a,b}] = c;
    }

    G.resize(N);
    D.resize(N);
    sort(F.begin(),F.end());
    UnionFind U(N);
    ll cost = 0;
    for (auto f: F) {
        if (U.unite(f.y.x, f.y.y)) {
            G[f.y.x].push_back({f.y.y, f.x});
            G[f.y.y].push_back({f.y.x, f.x});
            cost += f.x;
        }
    }

    P = vector2<pii>(L, N);
    dfs(0, -1, 0, 0);

    for (int i = 0; i < L-1; ++i) {
        for (int u = 0; u < N; ++u) {
            if (P[i][u].x != -1) {
                P[i+1][u] = {P[i][P[i][u].x].x, max(P[i][P[i][u].x].y, P[i][u].y)};
            }
        }
    }

    int Q; cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int u, v; cin >> u >> v; --u; --v;
        int a = u, b = v;
        if (D[a] < D[b]) swap(a, b);
        int cur = 0;
        for (int i = L-1; i >= 0; --i) {
            if (D[a] - (1<<i) >= D[b]) {
                cur = max(cur, P[i][a].y);
                a = P[i][a].x;
            }
        }

        for (int i = L-1; i >= 0; --i) {
            if (P[i][a].x != P[i][b].x) {
                cur = max(cur, P[i][a].y);
                cur = max(cur, P[i][b].y);
                a = P[i][a].x;
                b = P[i][b].x;
            }
        }

        if (a != b) {
            cur = max(cur, P[0][a].y);
            cur = max(cur, P[0][b].y);
            a = P[0][a].x;
            b = P[0][b].x;
        }

        cout << cost + C[{u,v}] - cur << '\n';
    }


}
};
