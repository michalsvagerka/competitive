#include "../l/lib.h"
// #include "../l/mod.h"

class DMagicBox {
public:
void solve(istream& cin, ostream& cout) {
    int X,Y,Z; cin >> X >> Y >> Z;
    int X1,Y1,Z1; cin >> X1 >> Y1 >> Z1;
    vector<int> A(6); cin >> A;
    int ans = 0;
    if (Y < 0) ans += A[0];
    if (Y > Y1) ans += A[1];
    if (Z < 0) ans += A[2];
    if (Z > Z1) ans += A[3];
    if (X < 0) ans += A[4];
    if (X > X1) ans += A[5];
    cout << ans << '\n';
}
};
