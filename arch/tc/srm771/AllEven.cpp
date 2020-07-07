#include "../../../l/lib.h"

class AllEven {
public:
    ll cnt(ll hi) {
        if (hi <= 0) {
            return 0LL;
        } else {
            if (hi == 1000000000000000000LL) hi = 999999999999999999LL;

            vector<int> D;
            ll x = hi;
            while (x) {
                D.push_back(x%10);
                x /= 10;
            }
            while (D.size() < 18) D.push_back(0);
            reverse(D.begin(),D.end());
            vector4<ll> E(19, 2, 2,1024, 0);
            E[0][0][0][0] = 1;
            for (int i = 0; i < 18; ++i) {
                for (int j = 0; j < 2; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 1024; ++l) {
                            for (int m = 0; m < 10; ++m) {
                                if (k == 0 && m > D[i]) continue;
                                int newJ = j || (m > 0);
                                int newK = k || (m < D[i]);
                                int newL = newJ ? (l^(1<<m)) : 0;
                                E[i+1][newJ][newK][newL] += E[i][j][k][l];
                            }
                        }
                    }
                }
            }
            ll ans = E[18][1][0][0] + E[18][1][1][0];
            return ans;
        }
    }
    long long countInRange(long long lo, long long hi) {
        return cnt(hi) - cnt(lo-1);
    }

    void solve(istream& cin, ostream& cout) {
        cout << countInRange(47, 999) << endl;
        cout << countInRange(47, 1010) << endl;
        cout << countInRange(12345678901LL, 98765432109LL) << endl;
        cout << countInRange(1234LL, 654321LL) << endl;
        cout << countInRange(0, 10) << endl;
        cout << countInRange(12345678901LL, 999999999999999999LL) << endl;
        cout << countInRange(12345678901LL, 1000000000000000000LL) << endl;
    }
};
