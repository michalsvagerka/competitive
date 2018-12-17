#include "../l/lib.h"
#include "../l/segtree.h"

class EWanderingTKHS {
public:
    vector<vector<int>> E, R;
    int N, T;
    vector<int> Enter, Exit, P, C;
    AddSumTree<int> G;
    vector<int> W, V;

    void dfs(int u, int p) {
        Enter[u] = T++;
        P[u] = p;
        for (int v : E[u]) if (v != p) dfs(v, u);
        Exit[u] = T;
    }

    void dfsClear(int u) {
        if (G.get(Enter[u]) == 1) {
            G.put(Enter[u], -1);
            for (int v : E[u]) if (v != P[u]) dfsClear(v);
        }
    }

    void dfs2(int u, int p) {
        for (int v : E[u]) {
            if (v != p) {
                V.push_back(v);
                W.push_back(max(W.back(), v));
                dfs2(v, u);
                W.pop_back();
                V.pop_back();
            }
        }

        if (u != 0) {
            G.put(Enter[u], 1);
            int j = bsh(0, int(V.size())-1, [&](int x) { return W[x] < u; });
            R[V[min(int(V.size())-1,j+2)]].push_back(u);
        }

        for (int r : R[u]) {
            int tot = G.get(Enter[r], Exit[r]-1);
            C[u] += tot;
            dfsClear(r);
        }
    }

    void dfs3(int u, int p) {
        for (int v : E[u]) if (v != p) {
            C[v] += C[u];
            dfs3(v, u);
        }
    }
    

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        R.resize(N);
        E.resize(N); Enter.resize(N); Exit.resize(N); P.resize(N);
        T = 0;
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        W.assign(1, 0);
        V.assign(1, 0);
        C.assign(N, 0);
        G.setup(N, 0);
        dfs(0, -1);
        dfs2(0, -1);
        dfs3(0, -1);
        C.erase(C.begin());
        cout << C;
    }
};
