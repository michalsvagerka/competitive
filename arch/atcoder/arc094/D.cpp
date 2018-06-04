#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            ll a, b; cin >> a >> b;
            if (a > b) swap(a,b);

            if (a == b) {
                cout << 2*a-2 << endl;
                continue;
            }

            int t = bsh(0, 1000000000, [&](int s) { return (ll)s*s < a*b; });
            ll ans = 2*min(t-a,b-t);
            if ((ll)t*(t+1)>=a*b) --ans;
            if (ans < b-a-1) ++ans;
            ans += 2*a-2;
            cout << ans << endl;
        }
    }
};
