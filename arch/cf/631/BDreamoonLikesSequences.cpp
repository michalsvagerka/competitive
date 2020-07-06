#include "../l/lib.h"
#include "../l/runtimemod.h"

class BDreamoonLikesSequences {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int D, M; cin >> D >> M;
            MOD = M;

            vector<RField> A(31, 0);
            A[0] = 1;
            for (int i = 0; i < 30; ++i) {
                int lo = 1<<i;
                int hi = 2*lo;
                for (int j = 0; j <= i; ++j) {
                    A[i+1] += A[j];
                }
                if (D < lo) A[i+1] = 0;
                else if (D >= hi) {
                    A[i+1] *= lo;
                } else {
                    A[i+1] *= (D-lo+1);
                }
            }
            RField ans = 0;
            for (int i = 1; i <= 30; ++i) ans += A[i];
            cout << ans << '\n';
        }
    }
};
