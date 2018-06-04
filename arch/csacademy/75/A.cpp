#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int D, t, v1, v2;
         cin >> D >> t >> v1 >> v2;
        if (v2 >= v1) {
            D += (v2-v1)*t;
            cout << (D+v1-1)/v1 + t << '\n';
        } else if (t*(v1-v2) >= D){
            cout << (D+v1-v2-1)/(v1-v2) << '\n';
        } else {
            D -= t*(v1-v2);
            cout << (D+v1-1)/v1 + t << '\n';
        }
    }
};
