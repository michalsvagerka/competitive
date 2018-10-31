#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int X, Y, Z, T1, T2, T3; cin >> X >> Y >> Z >> T1 >> T2 >> T3;

    int stairs = abs(Y-X) * T1;
    int elevator = (abs(Y-X) + abs(Z-X)) * T2 + 3 * T3;

    cout << (stairs >= elevator ? "YES" : "NO") << endl;
}
};
