#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int a,b,c; cin >> a >> b >> c;
        int d = max(a,max(b,c));
        int e = 3*d - a - b - c;
        if (e%2==1) {
            cout << (e+3)/2 << endl;
        } else {
            cout << e/2 << endl;
        }

    }
};
