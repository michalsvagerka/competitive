#include "../l/lib.h"
#include "../l/random.h"

class FFooFighters {
public:
    int N;
    vector<pair<int, ll>> X;
    vector<ll> Suf;

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        X.resize(N); cin >> X;

        ll base = 0;
        for (int i = 0; i < N; ++i) base += X[i].x;

        ll s = 0;
        for (int i = 0; i < 62; ++i) {
            ll j = 1LL<<i;
            ll k = 2LL<<i;
            ll cur = 0;
            for (auto x: X) {
                if (x.y >= j && x.y < k) {
                    cur += x.x;
                }
            }
            if (cur != 0 && (cur > 0) == (base > 0)) {
                s |= 1LL<<i;
                for (auto &x: X) {
                    if (x.y&1LL<<i) x.x = -x.x;
                }
            }
        }
        cout << s << endl;
    }
};
