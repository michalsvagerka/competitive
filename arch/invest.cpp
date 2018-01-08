#include "../l/lib.h"
// #include "../l/mod.h"

class invest {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int E, Y, D; cin >> E >> Y >> D;
            int mx = 1 + E / 20;
            vector<int> Z(mx, 0);
            for (int i = 0; i < D; ++i) {
                int V,I; cin >> V >> I; V /= 1000;
                for (int m = 0; m + V < mx; ++m) Z[m + V] = max(Z[m + V], Z[m] + I);
            }
            for (int y = 0; y < Y; ++y) E += Z[E/1000];
            cout << E << "\n";
        }

    }
};
