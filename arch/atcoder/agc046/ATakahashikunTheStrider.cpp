#include "../l/lib.h"

class ATakahashikunTheStrider {
public:
    void solve(istream& cin, ostream& cout) {
        int X; cin >> X;
        int S = 360 / gcd(X, 360);
        cout << S << endl;
    }
};
