#include "../l/lib.h"

class AOptimalCurrencyExchange {
public:
    void solve(istream& cin, ostream& cout) {
        int N, D, E; cin >> N >> D >> E;
        E *= 5;
        int ans = N;
        for (int i = 0; i * D <= N; ++i) {
            int j = (N-i*D)%E;
            ans = min(ans, j);
        }
        cout << ans << endl;
    }
};
