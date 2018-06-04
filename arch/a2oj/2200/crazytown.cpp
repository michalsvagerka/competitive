#include "../../../l/lib.h"
// #include "../l/mod.h"

class crazytown {
public:
    void solve(istream& cin, ostream& cout) {
        ll X1,Y1,X2,Y2;
        cin >> X1 >> Y1 >> X2 >> Y2;
        int N; cin >> N;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            ll a,b,c; cin >> a >> b >> c;
            bool d = a*X1 + b*Y1 > -c;
            bool e = a*X2 + b*Y2 > -c;
            ans += d != e;
        }
        cout << ans << '\n';
    }
};
