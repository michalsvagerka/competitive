#include "../l/lib.h"
// #include "../l/mod.h"

class APoisonousCookies {
public:
void solve(istream& cin, ostream& cout) {
    int A, B, C;
    cin >> A >> B >> C;
    cout << B + min(C, A+B+1) << endl;
}
};
