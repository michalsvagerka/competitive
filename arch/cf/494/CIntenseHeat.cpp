#include "../../../l/lib.h"

class CIntenseHeat {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        double ans = 0;
        for (int i = 0; i + K <= N; ++i) {
            int tot = 0;
            for (int j = 0; j < K; ++j) tot += A[i+j];
            for (int j = K; j + i <= N; ++j) {
                ans = max(ans, 1.0*tot/j);
                if (i+j!=N) tot += A[i+j];
            }
        }
        cout << fixed << setprecision(15) << ans << '\n';
    }
};
