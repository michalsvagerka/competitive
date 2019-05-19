#include "../l/lib.h"
// #include "../l/mod.h"

class DMultiplicationTable {
public:
    void solve(istream& cin, ostream& cout) {
        ll N, M, K; cin >> N >> M >> K;
        ll ans = bsl(0LL, N*M, [&](ll s) {
            ll tot = 0;
            for (int i = 1; i <= N; ++i) {
                tot += min(M, s/i);
            }
            return tot >= K;
        });
        cout << ans << endl;
    }
};
