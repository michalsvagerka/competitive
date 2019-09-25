#include "../l/lib.h"

class ETourism {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> W(N); cin >> W;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        int S; cin >> S; --S;

        vector<int> C(N);
        vector<pair<int, ll>> L;
        vector<ll> G(N, 0);
        vector<bool> R(N, false);
        for (int i = 0; i < N; ++i) {
            C[i] = E[i].size();
            if (C[i] == 1 && i != S) L.push_back({i, W[i]});
        }
        
        for (int i = 0; i < L.size(); ++i) {
            int u = L[i].x;
            ll c = L[i].y;
            R[u] = true;
            for (int v : E[u]) {
                if (!R[v]) {
                    C[v]--;
                    G[v] = max(G[v], c);
                    if (C[v] == 1 && v != S) {
                        L.push_back({v,G[v] + W[v]});
                    }
                }
            }
        }
        
        ll ans = 0;
        for (auto &l: L) ans = max(ans, l.y);
        for (int i = 0; i < N; ++i) if (!R[i]) ans += W[i];
        cout << ans << '\n';

    }
};
