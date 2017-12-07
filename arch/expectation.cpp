#include "../l/lib.h"
// #include "../l/mod.h"

class expectation {
public:
    double solve(int K) {
        double ans = 0.0;
        ll kk = K;
        vector<ll> O(30, 0);
        for (int i = 29; i > 0; --i) {
            if (K & (1<<i)) {
                for (int j = 0; j < i; ++j) {
                    O[j] += 1<<(i-1);
                }
                K ^= (1<<i);
                O[i] += K;
            }

            ans += (1<<i) * (2.0 * O[i]) * (kk - O[i]);
        }
        ans += (2.0 * O[0]) * (kk - O[0]);
        return ans / kk / kk;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) {
            int k; cin >> k;
            cout << fixed << setprecision(10) << solve(k) << "\n";
        }
    }
};
