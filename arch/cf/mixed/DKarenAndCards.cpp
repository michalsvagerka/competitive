#include "../l/lib.h"
#include "../l/nsegtree.h"

class DKarenAndCards {
public:
    void solve(istream& cin, ostream& cout) {
        ll N, P, Q, R; cin >> N >> P >> Q >> R;
        ll ans = P * Q * R;
        vector<vector<pii>> C(P);
        for (int i = 0; i < N; ++i) {
            int a, b, c; cin >> a >> b >> c;
            C[a-1].emplace_back(b-1,c);
        }

        AssignSumTree<ll> SS{(ui)Q, 0, 0};
        AssignMaxTree<int> ST{(ui)Q, 0, 0};

        for (int p = 0; p < P; ++p) {
            for (pii c: C[p]) {
                int ql = ST.longestSuffix([c](int v) { return v < c.y; });
                if (ql <= c.x) {
                    ST.put(ql, c.x, c.y);
                    SS.put(ql, c.x, c.y);
                }
            }
        }

        for (int p = P-1; p >= 0; --p) {
            for (pii c: C[p]) {
                ST.put(0, c.x, R);
                SS.put(0, c.x, R);
                int ql = ST.longestSuffix([c](int v) { return v < c.y; });
                if (ql <= Q-1) {
                    ST.put(ql, Q-1, c.y);
                    SS.put(ql, Q-1, c.y);
                }
            }
            ans -= SS.get(0, Q-1);
        }
        cout << ans << '\n';
    }
};
