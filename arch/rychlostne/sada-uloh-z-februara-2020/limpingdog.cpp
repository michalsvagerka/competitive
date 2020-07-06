#include "../l/lib.h"

class limpingdog {
public:
    void solve(istream& cin, ostream& cout) {
        vector<int> L(47*4, 1);
        for (int i = 2; i < L.size(); i += 4) L[i]++;
        for (int i = 0; i < L.size(); i += 47) L[i] += 42;
        ll T; cin >> T;
        T += 42;
        int tot = accumulate(L.begin(),L.end(),0);
        ll ans = (47 * 4) * (T / tot);
        T %= tot;
        int i = 0;
        while (L[i] <= T) {
            T -= L[i];
            ++i;
        }

        cout << ans + i << '\n';
    }
};
