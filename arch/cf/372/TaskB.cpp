#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:

    int N, M, L, S, T;
    vector<vector<pii>> E;
    vector<vector<pii>> F;

    void copyGraph(ll v, ll null) {
        int over = null ? v % null : 0;
        int single = null ? v / null : 0;
        
        F.clear();
        F.resize(N);
        
        for (int i = 0; i < N; ++i) {
            for (pii e: E[i]) {
                if (e.y == 0) {
                    if (i < e.x) {
                        int cost = single + (over-- > 0);
                        F[i].push_back({e.x, cost});
                        F[e.x].push_back({i, cost});
                    }
                } else {
                    F[i].push_back(e);
                }
            }
        }
    }

    ll cost() {
        minheap<pair<ll,int>> H;
        vector<ll> D(N, 1e18);
        D[S] = 0;
        H.push({0LL, S});
        while (!H.empty()) {
            auto h = H.top(); H.pop();
            if (D[h.y] != h.x) continue;
            for (pii f: F[h.y]) {
                if (f.y + h.x < D[f.x]) {
                    D[f.x] = f.y + h.x;
                    H.push({D[f.x], f.x});
                }
            }
        }

        return D[T];
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M >> L >> S >> T;
        E.resize(N);

        ll null = 0;

        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            E[u].push_back({v,w});
            E[v].push_back({u,w});
            null += w==0;
        }

        ll ans = bsh(null, null * L, [&](ll x) {
            copyGraph(x, null);
            return cost() <= L;
        });
        
        if (ans == -1) {
            cout << "NO\n";
        } else {
            copyGraph(ans, null);
            if (cost() != L) {
                cout << "NO\n";
            } else {

                cout << "YES\n";
                for (int i = 0; i < N; ++i) {
                    for (pii f: F[i]) {
                        if (i < f.x) {
                            cout << i << ' ' << f.x << ' ' << f.y << '\n';
                        }
                    }
                }
            }
        }
    }
};
