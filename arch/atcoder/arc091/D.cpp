#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N,K; cin >> N >> K;
        if (K == 0) {
            cout << ll(N)*N << endl;
            return;
        }
        ll ans = 0;
        for (int b = K+1; b <= N; ++b) {
            int f = N/b;
            ans += max(0, f*(b-K));
            ans += max(0, N%b - (K - 1));
        }
        cout << ans << endl;
    }
};
