#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    ll N, L, R, K;
    cin >> N >> L >> R >> K;
    ll Q = 1+(N+R-L)%N, ans = -1;
    auto check = [&](ll rev, ll take) {
        ll s = take - N, left = (K - Q) - rev * take;
        if (take >= N && take <= 2*N && left >= 0 && left <= min(Q,s) && min(Q, left + 1) + (N - Q) >= s)
            ans = max(ans, s);
    };
    
    for (ll rev = 0; rev <= 1000000; ++rev) {
        check(rev, (K-Q+N + N-Q+1)/(rev+1));
    }

    for (ll take = N; take <= min(2*N, 1000000LL); ++take) {
        check((K - 2*Q) / take, take);
        check((K - 2*Q) / take + 1, take);
    }

    cout << ans << endl;
}
};
