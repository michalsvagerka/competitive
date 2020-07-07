#include "../../../l/lib.h"

class CPaintTheTree {
public:
    int N, K;
    vector<vector<pii>> E;

    pair<ll, ll> dfs(int u, int p) {
        ll q = 0;
        vector<ll> W;
        for (pii v : E[u]) {
            if (v.x != p) {
                auto x = dfs(v.x, u);
                q += x.x;
                W.push_back(x.y + v.y - x.x);
            }
        }
        sort(W.begin(),W.end());
        reverse(W.begin(),W.end());

        ll satur = q, avail = q;
        for (int i = 0; i < K; ++i) {
            if (i >= W.size()) break;
            if (W[i] > 0) satur += W[i];
            if (i != K-1 && W[i] > 0) avail += W[i];
        }

        return {satur, avail};
    }

    void solve(istream& cin, ostream& cout) {
        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            cin >> N >> K;
            E.clear();
            E.resize(N);
            for (int i = 0; i < N - 1; ++i) {
                int u, v, w;
                cin >> u >> v >> w;
                --u; --v;
                E[u].push_back({v,w});
                E[v].push_back({u,w});
            }

            auto x = dfs(0, -1);
            cout << max(x.x, x.y) << '\n';
         }
    }
};
