#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> B(N-1);
        for (int i = 0; i < N - 1; ++i) {
            B[i] = abs(A[i+1] - A[i]);
        }
        for (int i = 1; i < N - 1; i += 2) {
            B[i] = -B[i];
        }

        ll lo = 0, hi = 0, cur = 0, ans = 0;
        for (int i = 0; i < N - 1; ++i) {
            cur += B[i];
            ans = max(ans, cur - lo);
            ans = max(ans, hi - cur);
            lo = min(lo, cur);
            hi = max(hi, cur);
        }
        cout << ans << endl;
    }
};
