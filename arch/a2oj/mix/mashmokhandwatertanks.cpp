#include "../../../l/lib.h"
// #include "../l/mod.h"

class mashmokhandwatertanks {
public:
    vector<vector<int>> E;
    vector<int> D;

    void dfs(int u, int p, int d) {
        D[d]++;
        for (int v:E[u]) if (v!=p) dfs(v,u,d+1);
    }
    
    void solve(istream& cin, ostream& cout) {
        int M, K, P; cin >> M >> K >> P;
        E.resize(M); D.resize(M);
        for (int i = 0; i < M - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1, 0);

        vector<int> R(M+1, 0);
        vector<ll> Q(M+1, 0);
        for (int m = 0; m < M; ++m) {
            R[m+1] = R[m] + D[m];
            Q[m+1] = Q[m] + m*D[m];
        }

        int ans = 0;
        for (int b = 1; b < M; ++b) {
            int l = bsl(1, b, [&](int t) {
                ll w = b*ll(R[b+1] - R[t]) - (Q[b+1] - Q[t]);
                return w <= P;
            });
            ll u = b*ll(R[b+1] - R[l]) - (Q[b+1] - Q[l]);
            int vert = R[b+1] - R[l];
            if (l!=1) vert += min(D[l-1], int(P-u)/(b-l+1));
            ans = max(vert, ans);
        }
        cout << min(ans, K) << endl;


    }
};
