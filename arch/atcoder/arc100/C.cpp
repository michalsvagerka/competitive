#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    for (int i = 0; i < N; ++i) {
        A[i] -= i+1;
    }
    sort(A.begin(),A.end());
    int b = A[N/2];

    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += abs(A[i]-b);
    }
    cout << ans << endl;
}
};
