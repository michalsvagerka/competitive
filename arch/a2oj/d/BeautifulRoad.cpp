#include "../l/lib.h"
 #include "../l/util.h"

class BeautifulRoad {
public:


    unordered_map<int, int> S;
    unordered_map<pii, ll> T;
    unordered_map<int, vector<int>> F;

    ll size(int u, int v) {
        int z = T[{u,v}];
        if (z) return z;

        int tot = dfs(u, -1);
        dfs2(u, -1, tot);
        return T[{u,v}];
    }

    int dfs(int u, int p) {
        int z = S[u];
        for (int v: F[u]) {
            if (v != p) z += dfs(v,u);
        }
        return z;
    }

    int dfs2(int u, int p, int tot) {
        int z = T[{u,p}];
        if (z) return z;

        z = S[u];
        for (int v:F[u]) {
            if (v != p) {
                z += dfs2(v, u, tot);
            }
        }

        for (int v:F[u]) {
            if (v != p) {
                T[{u,v}] = tot - T[{v,u}];
            }
        }
        return T[{u,p}] = z;
    }

void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    map<int, vector<pair<int,pii>>> E;
    for (int i = 0; i < N-1; ++i) {
        int u,v,d; cin >> u >> v >> d;
        E[d].push_back({i,{u-1,v-1}});
    }

    vector<ll> Ans(N-1, 0);
    UnionFind UF(N);

    for (auto&e : E) {
        S.clear();
        T.clear();
        F.clear();

        for (auto &ee: e.y) {
            int u = UF.find(ee.y.x);
            int v = UF.find(ee.y.y);
            S[u] = UF.size(u);
            S[v] = UF.size(v);
            F[u].push_back(v);
            F[v].push_back(u);
        }

        for (auto &ee: e.y) {
            int u = UF.find(ee.y.x);
            int v = UF.find(ee.y.y);
            Ans[ee.x] = 2 * size(u,v) * size(v,u);
        }

        for (auto &ee: e.y) {
            UF.unite(ee.y.x, ee.y.y);
        }
    }

    ll best = *max_element(Ans.begin(),Ans.end());
    int cnt = count(Ans.begin(),Ans.end(),best);
    vector<int> Edges;
    for (int i = 0; i < N; ++i) {
        if (Ans[i] == best) Edges.push_back(i+1);
    }
    cout << best << ' ' << cnt << endl << Edges;
}
};
