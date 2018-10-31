#include "../l/lib.h"
// #include "../l/mod.h"

class zigzagvec {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    vector<ll> A(N); cin >> A;
    ll ans = 1e18;
    for (int k : {-K, K}) {
        vector<ll> B = A;
        for (int i = 1; i < N; i += 2) { B[i] += k; }
        sort(B.begin(),B.end());
        ll cur = 0;
        for (int i = 0; i < N; ++i) cur += abs(B[i] - B[N/2]);
        ans = min(ans, cur);
    }
    cout << ans << endl;
}
};
