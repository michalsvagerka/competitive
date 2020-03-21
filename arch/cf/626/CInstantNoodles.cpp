#include "../l/lib.h"

class CInstantNoodles {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            vector<ll> C(N); cin >> C;
            vector<vector<int>> E(N);
            for (int i = 0; i < M; ++i) {
                int a, b; cin >> a >> b;
                --a; --b;
                E[b].push_back(a);
            }
            for (int i = 0; i < N; ++i) sort(E[i].begin(),E[i].end());
            map<vector<int>, ll> X;
            for (int i = 0; i < N; ++i) X[E[i]] += C[i];

            ll g = 0;
            for (auto &x: X) if (x.x.size() > 0) g = gcd(x.y, g);
            cout << g << '\n';
        }
    }
};
