#include "../../../l/lib.h"
// #include "../l/mod.h"

class pestremoc {
public:
    bool pestra(ll x) {
        stringstream ss;
        ss << x;
        string s = ss.str();
        vector<bool> R(10, false);
        for (char c:s) {
            if (R[c-'0']) return false;
            R[c-'0'] = true;
        }
        return true;
    }

    void solve(istream& cin, ostream& cout) {
        set<ll> P;
        for (ll n = 2; n < 100000; ++n) {
            ll y = n*n;
            while (y < 10000000000LL) {
                if (pestra(y)) P.insert(y);
                y *= n;
            }
        }
        cout << "1\n";
        for (ll p:P) {
            cout << p << '\n';
        }
    }
};
