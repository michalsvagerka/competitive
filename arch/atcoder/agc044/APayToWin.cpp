#include "../l/lib.h"

class APayToWin {
public:
    ll A, B, C, D;
    map<ll,ll> Cache;

    ll solve(ll N) {
        if (N < 0) return 1e18;
        if (N == 0) return 0;

        auto it = Cache.find(N);
        if (it != Cache.end()) return it->y;
        Cache[N] = 1e18;

        ll ans = 1e18;
        if (N < 3e9) ans = min(ans, N*D);
        for (int i = -1; i <= 1; ++i) {
            if ((N+i)%2 == 0) ans = min(ans, abs(i)*D + A + solve((N+i)/2));
        }
        for (int i = -2; i <= 2; ++i) {
            if ((N+i)%3 == 0) ans = min(ans, abs(i)*D + B + solve((N+i)/3));
        }
        for (int i = -4; i <= 4; ++i) {
            if ((N+i)%5 == 0) ans = min(ans, abs(i)*D + C + solve((N+i)/5));
        }
        return Cache[N] = ans;
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll N; cin >> N;
            cin >> A >> B >> C >> D;
            Cache.clear();
            cout << solve(N) << '\n';
        }
    }
};
