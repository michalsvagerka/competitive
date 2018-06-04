#include "../../../l/lib.h"
#include "../../../l/avl.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N, H; cin >> N >> H;

        vector<pii> B[2];
        for (int i = 0; i < N; ++i) {
            int x,y; cin >> x >> y;
            B[abs(x+y)%2].push_back({x,y});
        }

        ll ans = ll(N) * (ll(H)*2 - 2);
        for (auto &j : B) {
            vector<int> A, Q;
            for (pii b:j) {
                A.push_back(b.x + b.y - (H-1));
                Q.push_back(b.x - b.y);
            }
            sort(A.begin(),A.end());
            sort(Q.begin(),Q.end());

            for (pii b:j) {
                ans -= distance(lower_bound(A.begin(), A.end(), b.x + b.y - (H - 1) + 1), lower_bound(A.begin(), A.end(), b.x - b.y + (H-1) + 1));
                ans -= distance(lower_bound(Q.begin(), Q.end(), b.x - b.y + 1), lower_bound(Q.begin(), Q.end(), b.x + b.y + 1));
            }
        }

        cout << ans << endl;
    }
};
