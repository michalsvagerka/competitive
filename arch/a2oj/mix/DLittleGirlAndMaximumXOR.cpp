#include "../l/lib.h"
// #include "../l/mod.h"

class DLittleGirlAndMaximumXOR {
public:
    void solve(istream& cin, ostream& cout) {
        ll L, R; cin >> L >> R;
        for (int i = 62; i >= 0; --i) {
            if ((L^R)&(1LL<<i)) {
                cout << (2LL<<i)-1 << endl;
                return;
            }
        }

        cout << 0 << endl;
    }
};
