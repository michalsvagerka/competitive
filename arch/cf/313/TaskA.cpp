#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    vector<int> A(6); cin >> A;

    vector<int> R(A[1]+A[2], 0);
    R[0] = 2*A[0] + 1;
    for (int i = 1; i < A[1]+A[2]; ++i) {
        R[i] = R[i-1];
        R[i] += (i < A[1]);
        R[i] += (i < A[5]);
        R[i] -= (i > A[1]);
        R[i] -= (i > A[5]);
    }

//    cout << R;
    ll ans = 0;
    for (int r:R) ans += r;
    cout << ans << endl;
}
};
