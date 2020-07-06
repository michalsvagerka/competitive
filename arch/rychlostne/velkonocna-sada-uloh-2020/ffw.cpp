#include "../l/lib.h"

class ffw {
public:
    void solve(istream& cin, ostream& cout) {
        ll T; cin >> T;
        if (T <= 3) {
            cout << T << endl;
            return;
        }
        vector<ll> X(35, 1);
        for (int i = 1; i < 35; ++i) {
            X[i] = X[i-1] * 3;
        }

        ll ans = 2;
        T -= 4;
        int s = 1;
        while (T >= X[s] + X[s+1]) {
            T -= X[s] + X[s+1];
            ans += 2;
            s++;
        }
        while (T > 0) {
            while (T >= X[s]) {
                T -= X[s];
                ans++;
            }
            --s;
        }
        cout << ans << endl;
    }
};
