#include "../../../l/lib.h"

class CCandies {
public:
    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
        cout << bsl(1LL, N, [&](ll k) {
            ll v = 0;
            ll n = N;
            while (n) {
                v += min(k, n);
                n -= min(k, n);
                n -= n/10;
            }
            return 2*v >= N;
        }) << '\n';
    }
};
