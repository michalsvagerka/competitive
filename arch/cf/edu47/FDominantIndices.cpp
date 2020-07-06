#include "../l/lib.h"

class FDominantIndices {
public:
    struct Res {
        pii mx;
        map<int, int> B;
    };

    vector<int> Ans, D, P;
    vector<vector<int>> E;

    void dfs(int u, int p) {
        P[u] = p;
        if (p == -1) D[u] = 0; else D[u] = D[p]-1;
        for (int v : E[u]) {
            if (v != p) dfs(v, u);
        }
    }

    void dfs(int u, Res&r) {
        r.mx = {1,D[u]};
        r.B[D[u]] = 1;

        for (int v: E[u]) {
            if (v != P[u]) {
                Res t;
                dfs(v, t);
                if (t.B.size() > r.B.size()) swap(r,t);
                for (pii a: t.B) {
                    int b = r.B[a.x];
                    r.B[a.x] = b+a.y;
                    r.mx = max(r.mx, {b+a.y,a.x});
                }
            }
        }

        Ans[u] = D[u]-r.mx.y;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u,v; cin >> u >> v; u--; v--;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        D.resize(N); P.resize(N);
        Res r;
        Ans.assign(N, 0);
        dfs(0, -1);
        dfs(0, r);
        for (int ans: Ans) cout << ans << '\n';
    }
};
