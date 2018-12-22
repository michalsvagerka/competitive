#include "../l/lib.h"
// #include "../l/mod.h"

class zjazdmon {
public:
    vector<vector<int>> E,Q;
    vector<int> D,I;

    void dfs(int u, int d) {
        D[u] = d;
        for (int v :E[u]) dfs(v, d+1);
    }

    int dfs2(int u, int&deep) {
        int ans = 0;
        deep = -1;
        for (int v : E[u]) {
            int d;
            ans += dfs2(v, d);
            if (deep == -1 || (d!=-1 && D[deep] < D[d])) deep = d;
        }

        for (int q:Q[u]) if (deep == -1 || D[deep] < D[q]) deep = q;
        
        if (deep == u) {
            deep = -1;
            ans++;
        }

        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        int N, M, S;
        cin >> N >> M >> S;
        E.resize(N);
        I.assign(N, 0);
        D.assign(N, 0);
        Q.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            I[v]++;
        }

        for (int i = 0; i < N; ++i) if (!I[i]) dfs(i, 0);

        for (int i = 0; i < S; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            Q[b].push_back(a);
        }

        int ans = 0, d;
        for (int i = 0; i < N; ++i) if (!I[i]) ans += dfs2(i, d);
        cout << ans << '\n';
    }
};
