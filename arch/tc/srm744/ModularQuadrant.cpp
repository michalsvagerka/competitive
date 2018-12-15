#include "../l/lib.h"
// #include "../l/mod.h"

class ModularQuadrant {
public:

    ll cnt(int r, int c) {
        if (r == 0 || c == 0) return 0;
        if (r>c) swap(r,c);
        ll x = r; x -= x%3;
        ll y = c-x; y -= y%3;
        return 4*x/3 + x*x + (c%3 == 2)*r + y*r + (x+1)*(r%3 == 2);
    }

    ll sum(int r1, int r2, int c1, int c2) {
        ll ans = cnt(r2+1, c2+1) - cnt(r1, c2+1) - cnt(r2+1, c1) + cnt(r1, c1);
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << sum(0, 7, 0, 7) << endl;
        cout << sum(0, 7, 0, 5) << endl;
        cout << sum(0, 6, 0, 5) << endl;
        cout << sum(0, 5, 0, 5) << endl;
        cout << sum(0, 2, 1, 4) << endl;
        cout << sum(2, 2, 0, 7) << endl;
        cout << sum(4, 8, 0, 5) << endl;

    }
};
