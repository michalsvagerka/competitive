#include "../l/lib.h"
#include "../l/mod.h"

class hockeyplayoff {
public:
    void solve(istream& cin, ostream& cout) {
        int W; cin >> W;
        int PA, PB; cin >> PA >> PB;
        vector3<FieldMod> D(W+1, 2, 21, 0);
        D[0][0][0] = 1;

        FieldMod ans = 0;
        for (int i = 0; i < 2*W-1; ++i) {
            vector3<FieldMod> E(W+1, 2, 21, 0);
            for (int a = 0; a <= i; ++a) {
                int b = i-a;
                if (b >= W || b < 0 || a >= W) continue;
                for (int q = 0; q <= min(20, a); ++q) {
                    int pA = min(100, (((i&2)==0)?PA:(100-PB)) + q*5);
                    E[a+1][0][min(20, q+1)] += D[a][0][q] * pA;
                    E[a][1][1] += D[a][0][q] * (100 - pA);
                }

                for (int q = 0; q <= min(20, b); ++q) {
                    int pA = max(0, (((i&2)==0)?PA:(100-PB)) - q*5);
                    E[a+1][0][1] += D[a][1][q] * pA;
                    E[a][1][min(20, q+1)] += D[a][1][q] * (100 - pA);
                }
            }
            
            swap(E,D);
            ans *= 100;
            for (int q = 1; q <= min(20, W); ++q) {
                ans += D[W][0][q];
            }
        }

        cout << ans << '\n';
    }
};
