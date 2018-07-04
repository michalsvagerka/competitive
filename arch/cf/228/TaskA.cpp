#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    sort(A.begin(),A.end());
    for (int ans = 1; ans <= 100; ++ans) {
        bool ok = true;
        for (int i = 0; i < N; i+=ans) {
            for (int j = 0; j < ans; ++j) {
                if (i+j < N) ok &= A[i+j] >= i/ans;
            }
        }
        if (ok) {
            cout << ans << '\n';
            return;
        }

    }
}
};
