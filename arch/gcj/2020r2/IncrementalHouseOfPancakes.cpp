#include "../l/lib.h"

class IncrementalHouseOfPancakes {
public:
    void smart(ll &i, ll &L, ll&R) {

        if (L >= R) {
            ll j = bsh(1LL, 2000000000LL, [&](ll x) {
                return L - x * (x + 1) / 2 >= R;
            });
            if (j != -1) {
                i = j;
                L -= j * (j + 1) / 2;
            }
        } else if (R >= L) {
            ll j = bsh(1LL, 2000000000LL, [&](ll x) {
                return R - x * (x + 1) / 2 >= L;
            });
            if (j != -1) {
                R -= j * (j + 1) / 2;
                i = j;
            }
            if (R > L && R >= i+1) {
                i++;
                R -= i;
            }
        }

        while (i+1 <= max(L, R)) {
            ll z = bsh(0LL, 2000000000LL, [&](ll x) {
                ll left = (i+1)*x + x*(x-1);
                ll right = (i+2)*x + x*(x-1);
                if (left > L || right > R) return false;
                if (L-left-(i+2*x+1) >= R-right) {
                    return false;
                } else {
                    return true;
                }
            });
            ll left = (i+1)*z + z*(z-1);
            ll right = (i+2)*z + z*(z-1);
            L -= left;
            R -= right;
            i += 2*z;

            while (L >= R && L >= i+1) {
                ++i;
                L -= i;
            }

            while (R >= L && R >= i+1) {
                ++i;
                R -= i;
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll L, R; cin >> L >> R;
            ll i = 0;
            smart(i, L, R);
            cout << "Case #" << t+1 << ": " << i << ' ' << L << ' ' << R << '\n';
        }
    }
};
