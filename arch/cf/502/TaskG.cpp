#include "../l/lib.h"
 #include "../l/segtree.h"

class TaskG {
public:

    int N, Q;
    vector<vector<int>> E;
    vector<int> H, S, P, W, Enter, Exit;
    int T;
    AssignMaxTree<int> L;

    int dfs(int u) {
        S[u] = 1;
        for (int v:E[u]) {
            S[u] += dfs(v);
        }
        return S[u];
    }

    void dfs2(int u) {
        for (int v:E[u]) {
            if (2*S[v] >= S[u]) {
                H[u] = v;
            }
            dfs2(v);
        }
    }

    void dfs3(int u) {
        for (int i = 0; i < E[u].size(); ++i) {
            if (E[u][i] == H[u]) {
                swap(E[u][i],E[u][0]);
            }
        }
    }

    void dfs4(int u, int h) {
        W[u] = h;
        for (int v : E[u]) {
            if (v == H[u]) {
                dfs4(v, h);
            } else {
                dfs4(v, v);
            }
        }
    }

    void dfs5(int u) {
        Enter[u] = T++;
        for (int v :E[u]) {
            dfs5(v);
        }
        Exit[u] = T;
    }

void solve(istream& cin, ostream& cout) {
    cin >> N >> Q;
    E.resize(N);
    H = vector<int>(N, -1);
    P.resize(N);
    S.resize(N);
    W.resize(N); T = 0;
    Enter.resize(N);
    Exit.resize(N);
    P[0] = -1;
    for (int i = 1; i < N; ++i) {
        int p; cin >> p; --p;
        P[i] = p;
        E[p].push_back(i);
    }
    dfs(0);
    dfs2(0);
    dfs3(0);
    dfs4(0,0);
    dfs5(0);

    vector<int> J(N, -1);
    L.

    for (int q = 0; q < Q; ++q) {
        int t, u; cin >> t >> u;
        --u;
        if (t == 1) {

        } else if (t == 2) {

        } else {

        }
    }
}
};
