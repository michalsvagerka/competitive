#include "../l/lib.h"
// #include "../l/mod.h"

class CPushingBalls {
public:
void solve(istream& cin, ostream& cout) {
    int N;
    double D, X, ans = 0;
    cin >> N >> D >> X;
    D = 2*D + X;
    X *= 4;
    while (N > 0) {
        ans += D + double(N-1) * X/2;
        D += D/N;
        D += 1.5*X/N;
        X += 2*X/N;
        --N;
    }
    cout << fixed << setprecision(15) << ans/2 << endl;

}
};
