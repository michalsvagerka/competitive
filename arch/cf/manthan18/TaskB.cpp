#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, S; cin >> N >> S;
    vector<int> A(N); cin >> A;
    sort(A.begin(),A.end());
    ll ans = 0;
    for (int i = 0; i < N/2; ++i) {
        if (A[i] > S) ans += A[i] - S;
    }

    ans += abs(S-A[N/2]);
    
    for (int i = N/2+1; i < N; ++i) {
        if (A[i] < S) ans += S - A[i];
    }
    
    cout << ans << endl;

}
};
