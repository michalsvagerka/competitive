#include "../l/lib.h"
// #include "../l/mod.h"

class CLuckyDays {
public:
void solve(istream& cin, ostream& cout) {
    int LA, RA, TA, LB, RB, TB;
    cin >> LA >> RA >> TA >> LB >> RB >> TB;
    int ans = 0;
    int h = gcd(TA, TB);
    for (int a = LA / h; a <= LA / h + 1; ++a) {
        for (int b = LB / h; b <= LB / h + 1; ++b) {
            int d = LA - a * h, e = RA - a * h;
            int f = LB - b * h, g = RB - b * h;
            ans = max(ans, min(g, e) - max(d, f) + 1);
        }
    }
    
    if (LA == 0 && RA == TA - 1) ans = max(ans, RB - LB + 1);
    if (LB == 0 && RB == TB - 1) ans = max(ans, RA - LA + 1);
    cout << ans << '\n';
}
};

