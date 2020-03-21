#include "../l/lib.h"

class AAlyonaAndCopybooks {
public:
    void solve(istream& cin, ostream& cout) {
        ll N, A, B, C;
        cin >> N >> A >> B >> C;
        ll ans = 1e18;
        for (int a = 0; a <= 3; ++a) {
            for (int b = 0; b <= 3; ++b) {
                for (int c = 0; c <= 3; ++c) {
                    if ((N+a+2*b+3*c)%4==0) {
                        ans = min(ans, a*A+b*B+c*C);
                    }
                }
            }
        }
        cout << ans << '\n';
    }
};
