#include "../l/lib.h"

class ECompleteCompress {
public:
    string S;
    int N;
    vector<vector<int>> E;
    vector<int> SZ, P;
    vector<ll> D;
    vector<ll> UP;
    ll ans;
//
//    void dfs(int u, int p) {
//        P[u] = p;
//        SZ[u] = S[u] == '1';
//        D[u] = 0;
//        for (int v : E[u]) {
//            if (v != p) {
//                dfs(v, u);
//                SZ[u] += SZ[v];
//                D[u] += D[v];
//                D[u] += SZ[v];
//            }
//        }
//    }
//
//    void dfs2(int u, int cnt, ll depth) {
//        UP[u] = depth;
//        ll tot = 0;
//        for (int v : E[u]) if (v != P[u]) {
//            tot += D[v] + SZ[v];
//            cnt += SZ[v];
//        }
//
//        for (int v : E[u]) {
//            if (v != P[u]) {
//                ll mine = tot + cnt - (2*SZ[v] + D[v]);
//                dfs2(v, cnt - SZ[v], mine);
//            }
//        }
//    }

    int cnt(int u, int p, int d) {
        int ans = 0;
        if (S[u] == '1') ans += d;
        for (int v : E[u]) if (v != p) {
            ans += cnt(v, u, d+1);
        }
        return ans;
    }

    pair<int, pii> solve(int u, int p) {
        vector<pair<int, pii>> G;
        for (int v : E[u]) {
            if (v != p) {
                G.push_back(solve(v, u));
            }
        }

        int size = 0;
        int maxDepth = 0;
        int minDepth = 0;
        for (auto g: G) {
            maxDepth += g.y.y;
            size += g.x;
            minDepth += g.y.x;
        }

        int cur = maxDepth % 2;
        for (auto g: G) {
            int bst = max(0, g.y.x - (maxDepth - g.y.y));
            cur = max(cur, bst)
        }

        if (S[u] == '1') ++size;
//        cerr << u << ' ' << size << ' ' << cur + size << ' ' << maxDepth + size << endl;
        return {size, {cur + size, maxDepth + size}};

    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> S;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        int ans = 1000000000;
        for (int i = 0; i < N; ++i) {
            auto a = solve(i, -1);
//            cout << a << endl;
            if (a.y.x == a.x) {
                ans = min(ans, (a.y.y-a.y.x)/2);
            }
//            vector<ll> Q;
//            for (int v : E[i]) {
//                Q.push_back(cnt(v, i, 1));
////                if (v == P[i]) {
////                    Q.push_back(UP[i]);
////                } else {
////                    Q.push_back(D[v] + SZ[v]);
////                }
//            }
//            sort(Q.begin(),Q.end());
////            cout << Q << endl;
//            ll tot = 0;
//            for (ll q: Q) tot += q;
//            if (tot % 2 == 0 && Q.back() <= tot/2) {
//                ans = min(ans, tot/2);
//            }
        }
        if (ans < 1000000000) {
            cout << ans << endl;
        } else {
            cout << -1 << endl;
        }
    }
};
