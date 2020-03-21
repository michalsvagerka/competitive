#include "../l/lib.h"

class CJeremyBearimy {
public:
    int K;
    vector<vector<pii>> E;
    vector<int> S;
    
    pair<ll,bool> good(int u, int p) {
        ll ans = 0;
        bool up = true;
        for (pii v : E[u]) {
            if (v.x != p) {
                auto x = good(v.x, u);
                ans += x.x;
                if (x.y) {
                    up = !up;
                    ans += v.y;
                }
            }
        }
        return {ans,up};
    }
    
    int size(int u, int p) {
        S[u] = 1;
        for (pii v: E[u]) if (v.x != p) S[u] += size(v.x, u);
        return S[u];
    }
    
    int ctr(int u, int p) {
        for (pii v: E[u]) {
            if (v.x != p && S[v.x] > K) return ctr(v.x, u);   
        }
        return u;
    }
    
    pair<ll,int> bad(int u, int p) {
        int s = 1;
        ll ans = 0;
        for (pii v: E[u]) {
            if (v.x != p) {
                auto w = bad(v.x, u);
                ans += w.x;
                ans += w.y * ll(v.y);
                s += w.y;
            }
        }
        return {ans, s};
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> K;
            E.clear();
            E.resize(2*K);
            for (int i = 0; i < 2*K - 1; ++i) {
                int u, v, l;
                cin >> u >> v >> l;
                --u;
                --v;
                E[u].push_back({v,l});
                E[v].push_back({u,l});
            }
            S.resize(2*K);
            size(0, -1);
            int c = ctr(0, -1);
            
            auto G = good(0, -1);
            auto B = bad(c, -1);
            cout << G.x << ' ' << B.x << '\n';
        }
    }
};
