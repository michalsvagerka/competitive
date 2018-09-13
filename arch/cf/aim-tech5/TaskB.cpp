#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int Z = 2000;
    string A(Z, '4');
    string B(Z, '5');
    A[Z-1] = '5';
    cout << A << endl << B << endl;
}
};
