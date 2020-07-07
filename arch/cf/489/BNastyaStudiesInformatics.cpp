#include "../../../l/lib.h"

class BNastyaStudiesInformatics {
public:
    void solve(istream& cin, ostream& cout) {
        int L, R, X, Y;
        cin >> L >> R >> X >> Y;
        if (Y%X != 0) {
            cout << 0 << endl;
            return;
        }
        int S = Y/X;
        int ans = 0;
        for (int i = 1; i*i <= S; ++i) {
            if (S%i != 0 || gcd(i, S/i) != 1) continue;
            int a = X*i;
            int b = Y/i;
            if (L <= a && a <= R && L <= b && b <= R) {
                ans += 1 + (a!=b);
            }
        }
        cout << ans << endl;
    }
};
