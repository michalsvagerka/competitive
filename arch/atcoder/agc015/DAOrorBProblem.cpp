#include "../l/lib.h"

class DAOrorBProblem {
public:
    void solve(istream& cin, ostream& cout) {
        ll A, B;
        cin >> A >> B;
        if (A == B) {
            cout << 1 << endl;
            return;
        }

        for (ll l = 1LL<<60; l >= 1; l >>= 1) {
            if ((A&l) == (B&l)) {
                A &= ~l;
                B &= ~l;
            } else {
                B &= ~l;
                ll k = l;
                while (k >= 1 && (B&k) == 0) k >>= 1;
                cout << 2 * l - A + min(0LL, max(0LL, 2*k-1) + 1 - A) << endl;
                break;
            }
        }
    }
};
