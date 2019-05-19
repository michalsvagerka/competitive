#include "../l/lib.h"

constexpr ll INF = 1e18;

class DProfessionalLayer {
public:

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        ll K; cin >> K;
        vector<ll> A(N); cin >> A;
        vector<int> E(N); cin >> E;

        ll g = A[0];
        for (ll a:A) g = gcd(g, a);

        if (g == 1) {
            cout << 0 << endl;
            return;
        }

        ll gg = g;
        vector<ll> F;
        for (ll x = 2; x*x <= g; ++x) {
            if (g%x == 0) {
                while (g % x == 0) g /= x;
                F.push_back(x);
            }
        }
        if (g != 1) F.push_back(g);
        int M = F.size();

        map<ll, vector<pii>> H;
        for (int j = 0; j < N; ++j) {
            ll X = A[j]/gg;
            for (int k = 0; k < M; ++k) while (X % F[k] == 0) X /= F[k];
            auto &h = H[A[j]/X];
            h.emplace_back(E[j], j);
        }

        vector<vector<pii>> U(1<<M);
        for (auto&h:H) {
            sort(h.y.begin(), h.y.end());
            if (h.y.size() > M) h.y.resize(M);

            vector<ll> P(M, 1);
            ll X = h.x;
            for (int i = 0; i < M; ++i) while (X % F[i] == 0) { P[i] *= F[i]; X /= F[i]; }
            for (int i = 1; i < (1<<M); ++i) {
                ll p = 1;
                for (int k = 0; k < M; ++k) if (i&(1<<k)) p *= P[k];
                if (p <= K) {
                    for (pii hh : h.y) U[i].push_back(hh);
                }
            }
        }

        map<int, vector<int>> G;
        for (int i = 1; i < (1<<M); ++i) {
            sort(U[i].begin(),U[i].end());
            if (U[i].size() > M) U[i].resize(M);
            for (pii u: U[i]) G[u.y].emplace_back(i);
        }

        vector2<ll> D(1<<M, M+1, INF);
        D[0][0] = 0;
        for (auto &g: G) {
            auto Q = D;
            for (int i = 0; i < (1<<M); ++i) {
                for (int k = 0; k < M; ++k) {
                    if (D[i][k] == INF) continue;

                    for (int j : g.y) {
                        if ((i & j) == 0) {
                            Q[i|j][k+1] = min(Q[i|j][k+1], D[i][k] + E[g.x]);
                        }
                    }
                }
            }
            swap(Q,D);
        }

        ll ans = INF;
        for (int i = 1; i <= M; ++i) ans = min(ans, D.back()[i] * i);
        if (ans == INF) cout << "-1\n";
        else cout << ans << endl;
    }
};
