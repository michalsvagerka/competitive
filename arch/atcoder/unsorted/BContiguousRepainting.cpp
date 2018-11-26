#include "../l/lib.h"
// #include "../l/mod.h"

class BContiguousRepainting {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    vector<int> A(N); cin >> A;
    vector<ll> P(N+1, 0), Q(N+1, 0);
    for (int i = 0; i < N; ++i) {
        P[i+1] = P[i] + A[i];
        Q[i+1] = Q[i] + max(A[i], 0);
    }

    ll ans = -1e18;
    for (int i = 0; i + K <= N; ++i) {
        ll left = Q[i];
        ll right = Q[N] - Q[i+K];
        ll mid = P[i+K] - P[i];
        ans = max(ans, left + right + max(mid, 0LL));
    }
    cout << ans << '\n';
}
};
