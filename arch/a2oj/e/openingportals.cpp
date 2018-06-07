#include "../../../l/lib.h"
 #include "../../../l/util.h"

class openingportals {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M;
        cin >> N >> M;
        vector<vector<pii>> E(N);
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u;
            --v;
            E[u].push_back({v,w});
            E[v].push_back({u,w});
        }

        int K; cin >> K;
        vector<bool> P(N, false);
        for (int i = 0; i < K; ++i) { int p; cin >> p; P[p-1] = true; }

        vector<ll> D(N, 1e16);
        vector<int> S(N, -1);
        minheap<pair<ll,int>> Q;
        for (int i = 0; i < N; ++i) {
            if (P[i]) {
                Q.push({0,i});
                S[i] = i;
                D[i] = 0;
            }

        }
        while (!Q.empty()) {
            auto q = Q.top(); Q.pop();
            if (D[q.y] != q.x) continue;

            for (pii v:E[q.y]) {
                ll d = q.x + v.y;
                if (D[v.x] > d) {
                    D[v.x] = d;
                    S[v.x] = S[q.y];
                    Q.push({d,v.x});
                }
            }
        }


        vector<pair<ll,pii>> F;
        for (int i = 0; i < N; ++i) {
            for (pii j : E[i]) {
                if (i < j.x) {
                    F.push_back({D[i] + D[j.x] + j.y, {S[i],S[j.x]}});
                }
            }
        }
        sort(F.begin(),F.end());


        ll ans = 0;
        UnionFind U(N);
        for (auto&f:F) {
            if (U.unite(f.y.x,f.y.y)) ans += f.x;
        }
        if (!P[0])  ans += D[0];

        cout << ans << endl;
    }
};
