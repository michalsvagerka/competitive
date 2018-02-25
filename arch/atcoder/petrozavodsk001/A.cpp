#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int X, Y; cin >> X >> Y;
        if (X % Y == 0) {
            cout << "-1\n";
        } else {
            cout << X << endl;
        }

    }
};
