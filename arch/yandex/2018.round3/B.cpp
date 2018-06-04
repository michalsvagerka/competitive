#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        for (int i = 0; i < N-1; ++i) {
            if (A[i+1] == 0 && A[i] != 0) {
                cout << -1 << endl;
                return;
            }
        }

        ll ans = 0;
        int left = 0;
        for (int i = 1; i < N; ++i) {
            while (A[i] < A[i-1]) {
                A[i] *= 2;
                ans++;
            }
            ans += left;
            if (A[i] > 1e7) {
                A[i] /= 2;
                left++;
            }
        }

        cout << ans << endl;
    }
};
