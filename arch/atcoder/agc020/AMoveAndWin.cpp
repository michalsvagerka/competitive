#include "../l/lib.h"

class AMoveAndWin {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B; cin >> N >> A >> B;
        if ((A+B)%2 == 0) {
            cout << "Alice\n";
        } else {
            cout << "Borys\n";
        }
    }
};
