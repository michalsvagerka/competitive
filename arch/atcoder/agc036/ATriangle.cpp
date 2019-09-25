#include "../l/lib.h"

class ATriangle {
public:
    void solve(istream& cin, ostream& cout) {
        ll S; cin >> S;
        ll b = bsl(1LL, 1000000000LL, [&](ll a) {
            return a * a >= S;
        });
        if ((b-1) * b >= S) {
            cout << 0 << ' ' << 0 << ' ' << 1 << ' ' << b-1 << ' ' << b << ' ' << b*(b-1) - S << endl;
        } else {
            cout << 0 << ' ' << 0 << ' ' << 1 << ' ' << b << ' ' << b << ' ' << b*b - S << endl;

    }
};
