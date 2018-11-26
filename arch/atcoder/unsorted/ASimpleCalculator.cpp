#include "../l/lib.h"
// #include "../l/mod.h"

class ASimpleCalculator {
public:
void solve(istream& cin, ostream& cout) {
    int X, Y; cin >> X >> Y;
    int ans = 0;
    if (abs(X) > abs(Y)) {
        if (X > 0) {
            ans++;
            X = -X;
        }


    } else if (abs(X) < abs(Y)) {
        if (X < 0) {
            ans++;
            X = -X;
        }
    }

    ans += abs(abs(Y) - abs(X));
    X += abs(abs(Y) - abs(X));
    ans += X!=Y;

    cout << ans << '\n';
}
};
