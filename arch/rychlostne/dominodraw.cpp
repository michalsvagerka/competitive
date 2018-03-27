#include "../../l/lib.h"
// #include "../l/mod.h"

class dominodraw {
public:
    void solve(istream& cin, ostream& cout) {
        ll S; cin >> S;
        if (S%2==1) {
            cout << "0 0\n0 0\n0 0\n0 0\n";
            return;
        }
        S /= 2;
        for (ll i = 0; i*i <= S; ++i) {
            ll j = sqrt(S-i*i);
            if (i*i+j*j == S) {
                cout << 0 << ' ' << j << '\n'
                     << i << ' ' << 0 << '\n'
                     << 2*j << ' ' << j+2*i << '\n'
                     << 2*j+i << ' ' << 2*i << '\n';
                return;
            }
        }
        cout << "0 0\n0 0\n0 0\n0 0\n";
    }
};
