#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    void solve(istream& cin, ostream& cout) {
        int N, D, B; cin >> N >> D >> B;
        vector<int> A(N); cin >> A;

        int ans = 0;
        for (int j = 1; j >= 0; --j) {
            int last = -1, end = -1;
            int cnt = 0, bad = 0;
            for (int i = 0; i < (N+j) / 2; ++i) {
                end = min(N-1, end + D + 1);
                while (last < end) {
                    cnt += A[++last];
                }
                if (cnt >= B) {
                    cnt -= B;
                } else {
                    bad++;
                }
            }

            //cout << cnt + B*((N+j) / 2-bad) << ' ' << N*B << endl;
            ans = max(ans, bad);

            reverse(A.begin(),A.end());
        }

        cout << ans << endl;
    }
};
