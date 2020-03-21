#include "../l/lib.h"
#include "../l/primes.h"

class diophantine {
public:
    void solve(istream& cin, ostream& cout) {
        int N, D; cin >> N >> D;

        auto P = Sieve{50000}.primes();
        P.resize(N+D);
        vector<ll> Q(N);
        for (int i = 0; i < N; ++i) Q[i] = ll(P[i]) * ll(P[i+D]);

        unordered_map<ll, int> Z;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (Q[j] >= Q[i] + 3*Q[0]) {
                    Z[Q[j]-Q[i]-Q[0]]++;
                }
            }
        }

        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                ans += Z[Q[i] + Q[j]];
            }
            ans += 2 * Z[Q[i] + Q[i]];
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                ans += (3*Q[i] + Q[0] == Q[j]);
            }
        }

        assert(ans % 3 == 0);

        cout << ans/3 << '\n';
    }
};
