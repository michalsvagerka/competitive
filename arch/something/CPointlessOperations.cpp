#include "../l/lib.h"
// #include "../l/mod.h"

class CPointlessOperations {
public:
void solve(istream& cin, ostream& cout) {
    vector<ll> R(41, 1);
    for (int i = 1; i <= 40; ++i) {
        ll x = (1LL<<i)-1;
        for (ll j = 2; j*j <= x; ++j) {
            if (x%j == 0) {
                R[i] = x/j;
                break;
            }
        }
    }
    
    int Q; cin >> Q;
    for (int q = 0; q < Q; ++q) {
        ll A; cin >> A;
        auto x = logceil(A);
        if (A == (1LL<<x)-1) {
            cout << R[x] << '\n';
        } else {
            cout << (1LL<<x)-1 << '\n';
        }
    }
}
};
