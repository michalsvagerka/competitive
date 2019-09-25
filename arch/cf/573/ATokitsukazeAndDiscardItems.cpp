#include "../l/lib.h"

class ATokitsukazeAndDiscardItems {
public:
    void solve(istream& cin, ostream& cout) {
        ll N, K;
        int M; cin >> N >> M >> K;
        vector<ll> P(M); cin >> P;
        for (ll&p: P) --p;
        int ans = 0;
        for (int i = 0; i < M; ) {
            ll act = P[i] - i;
            ll low = act - act % K + i;
            ++i;
            while (i < M && P[i] < low + K) ++i;
            ++ans;
        }

        cout << ans << '\n';
    }
};
