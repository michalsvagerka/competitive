#include "../l/lib.h"
 #include "../l/mod.h"
#include "../l/graph.h"
#include "../l/bridges.h"
#include "../l/util.h"

class Cactus {
public:

    void dfs(int u, int p, vector<int>&B, const vector<vector<int>>&E) {
        if (p != -1) B[u] += B[p];
        for (int v:E[u]) if (v != p) dfs(v, u, B, E);
    }

void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<vector<int>> E(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    vector<pii> Bridges;
    Graph G{E};
    G.bridges(Bridges);
    set<pii> BS;
    for (pii&br:Bridges) BS.insert(br);

    UnionFind U(N);
    for (int u = 0; u < N; ++u) {
        for (int v:E[u]) {
            if (BS.find({u,v}) == BS.end() && BS.find({v,u}) == BS.end()) {
                U.unite(u,v);
            }
        }
    }

    map<int, int> Comp;
    vector<int> Big(U.comp, 0);
    Tree T(U.comp);
    for (int u = 0; u < N; ++u) {
        int c = U.find(u);
        auto it = Comp.find(c);
        if (it == Comp.end()) {
            int g = Comp.size();
            Comp[c] = g;
        } else {
            Big[it->y] = 1;
        }
    }

    
    for (pii&br : Bridges) {
        int u = Comp[U.find(br.x)];
        int v = Comp[U.find(br.y)];
        T.addEdge(u,v);
    }

    T.calcLA();
    auto Huge = Big;
    dfs(0, -1, Huge, T.E);

    int K; cin >> K;
    for (int i = 0; i < K; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        a = Comp[U.find(a)];
        b = Comp[U.find(b)];
        if (a == b) cout << (1+Big[a]) << '\n';
        else {
            int l = T.lca(a, b);
            int big = Huge[a] + Huge[b] - 2 * Huge[l] + Big[l];
            cout << FieldMod{2}.pow(big) << '\n';
        }
    }


}
};
