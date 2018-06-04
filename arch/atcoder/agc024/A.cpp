#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int A,B,C;
        ll K;
        cin >> A >> B >> C >> K;
        K %= 2;
        if (K == 1) {
            cout << B-A << '\n';
        } else {
            cout << A-B << '\n';
        }
    }
};
