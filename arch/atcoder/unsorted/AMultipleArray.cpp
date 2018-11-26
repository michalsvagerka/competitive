#include "../l/lib.h"
// #include "../l/mod.h"

class AMultipleArray {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<ll> A(N), B(N);
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];

    ll ans = 0;
    for (int i = N-1; i >= 0; --i) {
        A[i] += ans;
        ll mod = A[i] % B[i];
        if (mod != 0) {
            ans += B[i] - mod;
            A[i] += B[i] - mod;
        }
    }
    cout << ans << '\n';
}
};
