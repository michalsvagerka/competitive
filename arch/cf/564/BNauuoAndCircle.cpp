#include "../l/lib.h"
#include "../l/mod.h"
typedef Field<998244353> FF;
class BNauuoAndCircle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> D(N, 0);
        for (int i = 0; i < 2*N-2; ++i) {
            int u; cin >> u; D[u-1]++;
        }

        auto F = FF::fact(200001);
        FF ans = N;
        for (int i = 0; i < N; ++i) {
            ans *= F[D[i]];
        }
        cout << ans << '\n';
    }
};
