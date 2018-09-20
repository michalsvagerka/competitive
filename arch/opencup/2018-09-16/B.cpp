#include "../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    vector<vector<int>> E;
    void dfs(int u, int p, ll&edgeRem, ll &vertexRem, ll &dead) {
        if (E[u].size() == 1) {
            edgeRem = 1e9;
            vertexRem = 1e9;
            dead = 0;
            return;
        }

        vector<ll> D(4, 1e9); // (removed, needs removal, nothing, has odd edge)
        D[2] = 0;
        for (int v:E[u]) {
            if (v != p) {
                dfs(v, u, edgeRem, vertexRem, dead);
                vector<ll> E(4, 1e9);

                E[0] = min(min(D[0] + dead, D[0] + vertexRem), min(D[0], D[3]) + edgeRem + 1);
                E[1] = min(min(D[1], D[2]) + dead, D[1] + vertexRem);
                E[2] = D[2] + vertexRem;
                E[3] = min(D[3] + min(vertexRem, dead), edgeRem + min(D[1], D[2]));
                swap(D,E);
            }
        }

        dead = D[2];
        vertexRem = D[0];
        edgeRem = min(D[1], D[3]);
    }
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    if (N <= 3) { cout << 1 << endl; return; }
    E.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int u,v; cin >> u >> v;
        --u; --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    int root = 0;
    while (E[root].size() == 1) ++root;

    ll edgeRem, vertexRem, dead;
    dfs(root, -1, edgeRem, vertexRem, dead);

    ll ans = min(edgeRem + 1, min(dead, vertexRem));
    cout << ans << endl;
}
};
