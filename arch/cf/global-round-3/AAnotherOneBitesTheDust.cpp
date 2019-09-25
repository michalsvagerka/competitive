#include "../l/lib.h"

class AAnotherOneBitesTheDust {
public:
    void solve(istream& cin, ostream& cout) {
        ll a, b, c; cin >> a >> b >> c;
        cout << 2*c + 2*min(a,b) + (a!=b) << endl;
    }
};
