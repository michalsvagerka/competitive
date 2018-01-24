#include "../l/lib.h"
// #include "../l/mod.h"

class pasiky {
public:
    ll count(int x,int y) {
        if (x > y) swap(x,y);
        ll p = x/2, l = y/2 - x/2;
        return 3*p + 2*p*(p-1) + l*x;
    }

    void solve(istream& cin, ostream& cout) {
        do {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << count(x2, y2) + count(x1, y1) - count(x1, y2) - count(x2, y1) << endl;
        } while (!cin.eof());
    }
};
