#include "../l/lib.h"
#include "../l/runtimemod.h"

class CNewYearAndPermutation {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N >> MOD;
        RField ans = 0;
        auto F = RField::fact(N+1);
        for (int i = 1; i <= N; ++i) {
            ans += F[i] * F[N-i] * (N-i+1) * (N-i+1);
        }
        cout << ans << '\n';
    }
};
