#include "../l/lib.h"

class BCountPairs {
public:
    void solve(istream& cin, ostream& cout) {
        int N, P, K; cin >> N >> P >> K;
        vector<ll> A(N); cin >> A;
        map<ll, int> Cnt;
        ll ans = 0;
        for (ll a: A) {
            ll asq = a*a%P;
            ll a4 = asq*asq%P;
            ll ka = K*a%P;
            ll dif = ((a4-ka)%P+P)%P;
            ans += Cnt[dif];
            Cnt[dif]++;
        }
        cout << ans << '\n';
    }
};
