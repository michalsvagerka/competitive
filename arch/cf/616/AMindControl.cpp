#include "../l/lib.h"

class AMindControl {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M, K; cin >> N >> M >> K;
            vector<int> A(N); cin >> A;
            int ans = 0;
            if (K >= M) K = M-1;
            int B = M-1-K;
            for (int i = 0; i <= K; ++i) {
                int cur = 1e9;
                for (int j = 0; j <= B; ++j) {
                    cur = min(cur, max(A[i+j], A[N-1-(K-i)-(B-j)]));
                }
                ans = max(ans, cur);
            }
            cout << ans << '\n';
        }
    }
};
