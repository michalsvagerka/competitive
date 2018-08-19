#include "../l/lib.h"
// #include "../l/mod.h"

class FlatlandFencing {
public:
void solve(istream& cin, ostream& cout) {
    int X,Y,A,B; cin >> X >> Y >> A >> B;
    bool sw = false;
    if (X > Y) {
        sw = true;
        swap(X,Y);
        swap(A,B);
        A = -A;
        B = -B;
    }
    if (Y-X <= B && Y-X >= A) {
        cout << "FIRST\n" << (sw?X:Y) << '\n';
    } else if (A <= 0) {
        cout << "DRAW\n";
    } else {
        int D = (Y-X-1)%(A+B)+1;
        if (D == A+B) {
            cout << "SECOND\n";
        } else if (D > B) {
            cout << "DRAW\n";
        } else if (D >= A) {
            cout << "FIRST\n" << (sw?Y-D:X+D) << '\n';
        } else {
            cout << "DRAW\n";
        }
    }
}
};
