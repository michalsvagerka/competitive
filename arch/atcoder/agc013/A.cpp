#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int ans = 1, b = 0;
        for (int i = 1; i < N; ++i) {
            if ((A[b] < A[i-1] && A[i-1] > A[i]) || (A[b] > A[i-1] && A[i-1] < A[i])) {
                ++ans;
                b = i;
            }
        }
        cout << ans << endl;
    }
};
