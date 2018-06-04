#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        if (A[0] != 0) {
            cout << "-1\n";
            return;
        }

        ll ans = 0;
        for (int i = 1; i < N; ++i) {
            if (A[i] > A[i-1]+1) {
                cout << "-1\n";
                return;
            } else if (A[i] == A[i-1]+1) {
                ans++;
            } else {
                ans += A[i];
            }
        }
        cout << ans << '\n';
    }
};
