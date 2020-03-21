#include "../l/lib.h"

class dorovnaj {
public:
    void solve(istream& cin, ostream& cout) {
        ll A, B, C; cin >> A >> B >> C;
        cout << A + B + C - 3*(min(A,min(B,C))) << endl;
    }
};
