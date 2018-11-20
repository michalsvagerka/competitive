#include "../l/lib.h"
 #include "../l/random.h"

class FTreeAndXOR {
public:
    int N;
    ll K;
    vector<vector<pair<int,ll>>> E;
    vector<ll> G;

    void dfs(int u, ll x) {
        G[u] = x;
        for (auto v:E[u]) {
            dfs(v.x, x ^ v.y);
        }
    }

    struct Node {
        Node *p[2];
        int cnt;
    };


    void solve(istream& cin, ostream& cout) {
        cin >> N >> K;
        if (N == -1) {
            N = 1e6;
            G.resize(N);
            random_ll R{0, (1LL<<62)-1};
            for (int i = 0; i < N; ++i) {
                G[i] = R(rng);
            }
        } else {
            E.resize(N);
            G.resize(N);
            for (int i = 0; i < N - 1; ++i) {
                int p;
                ll w;
                cin >> p >> w;
                E[p - 1].push_back({i + 1, w});
            }
            dfs(0, 0LL);
        }

        sort(G.begin(),G.end());
        vector<pii> W1{{0,G.size()}}, W2{{0,0}};
        ll ans = 0;
        for (int h = 61; h >= 0; --h) {
            vector<pii> X1, X2;
            ll cnt = 0;
            for (int i = 0; i < W1.size(); ++i) {
                int a = 0, c = 0;
                for (int g = W1[i].x; g < W1[i].y; ++g) a += (G[g]>>h)&1;
                for (int g = W2[i].x; g < W2[i].y; ++g) c += (G[g]>>h)&1;
                int b = W1[i].y - W1[i].x - a, d = W2[i].y - W2[i].x - c;
                if (ans == 0) { c = a; d = b; }
                cnt += ll(a) * c + ll(b) * d;
            }
            if (ans) cnt *= 2;

            if (cnt < K) {
                for (int i = 0; i < W1.size(); ++i) {
                    int a = W1[i].x, c = W2[i].x;
                    while (a < W1[i].y && !((G[a]>>h)&1)) ++a;
                    while (c < W2[i].y && !((G[c]>>h)&1)) ++c;

                    if (ans == 0) {
                        if (W1[i].x != a && W1[i].y != a) { X1.emplace_back(W1[i].x, a); X2.emplace_back(a, W1[i].y); }
                    } else {
                        if (W1[i].x != a && W2[i].y != c) { X1.emplace_back(W1[i].x, a); X2.emplace_back(c, W2[i].y); }
                        if (W1[i].y != a && W2[i].x != c) { X1.emplace_back(a, W1[i].y); X2.emplace_back(W2[i].x, c); }
                    }
                }
                ans |= (1LL<<h);
                K -= cnt;
            } else {
                for (int i = 0; i < W1.size(); ++i) {
                    int a = W1[i].x, c = W2[i].x;
                    while (a < W1[i].y && !((G[a]>>h)&1)) ++a;
                    while (c < W2[i].y && !((G[c]>>h)&1)) ++c;

                    if (W1[i].x != a && (W2[i].x != c || ans == 0)) { X1.emplace_back(W1[i].x, a); X2.emplace_back(W2[i].x, c); }
                    if (W1[i].y != a && (W2[i].y != c || ans == 0)) { X1.emplace_back(a, W1[i].y); X2.emplace_back(c, W2[i].y); }
                }
            }
            swap(X1, W1);
            swap(X2, W2);
        }
        cout << ans << '\n';

    }
};
