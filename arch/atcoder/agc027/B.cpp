#include "../l/lib.h"
// #include "../l/mod.h"

class B {
public:
void solve(istream& cin, ostream& cout) {
    ll N, P; cin >> N >> P;
    vector<ll> X(N); cin >> X;
    vector<ll> F(N+1, 0);
    for (int i = 0; i < N; ++i) F[i+1] = F[i] + X[i];

    __int128 ans;
    for (int t = 1; t <= N; ++t) {
        __int128 cost = 0;
        __int128 z = 5;
        for (int i = 0; i < N; i += t) {
            int r = min(i+t,(int)N);
            cost += z * (F[N-i] - F[N-r]);
            if (i != 0) z += 2;
        }
        cost += (N+t) * P;
        if (t == 1) ans = cost;
        else ans = min(ans, cost);
    }
    cout << ll(ans) << '\n';
}
};
