#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    vector<vector<int>> E;
    vector<bool> V;
    vector<pii> Q;
    vector<int> Z,B,D,F;
    int N, M, W;

    pii dfs(int u) {
        if (V[u]) return {0,0};
        V[u] = true;
        pii ans = {Z[u],B[u]};

        for (int i = Z[u]; i <= W; ++i) {
            F[i] = max(F[i], D[i-Z[u]] + B[u]);
        }
        for (int v:E[u]) {
            pii ret = dfs(v);
            ans.x += ret.x;
            ans.y += ret.y;
        }
        return ans;
    }

void solve(istream& cin, ostream& cout) {
    cin >> N >> M >> W;
    Z.resize(N);
    B.resize(N);
    cin >> Z >> B;
    E.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    V = vector<bool>(N, false);
    D = vector<int>(W+1, 0);

    for (int i = 0; i < N; ++i) {
        F = D;
        if (!V[i]) {
            pii all = dfs(i);
            for (int i = all.x; i <= W; ++i) {
                F[i] = max(F[i], D[i-all.x] + all.y);
            }
        }
        swap(F,D);
    }

    cout << D[W] << '\n';
}
};
