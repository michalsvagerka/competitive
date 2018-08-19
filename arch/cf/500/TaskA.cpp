#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(2*N); cin >> A;
    sort(A.begin(),A.end());
    ll ans = ll(A[N-1]-A[0]) * ll(A[2*N-1]-A[N]);
    for (int i = 1; i < N; ++i) {
        ans = min(ans, ll(A[2*N-1]-A[0]) * ll(A[i+N-1] - A[i]));
    }
    cout << ans << endl;
}
};
