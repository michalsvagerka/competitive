#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> F;

class BRGBBalls {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;

        F ans = 1;
        int b = 0, r = 0, g = 0;
        int br = 0, bg = 0, rg = 0;
        for (int i = 0; i < 3*N; ++i) {
            switch (S[i]) {
                case 'R': {
                    if (bg > 0) {
                        ans *= bg;
                        --bg;
                    } else if (b > 0) {
                        ans *= b;
                        --b;
                        ++br;
                    } else if (g > 0) {
                        ans *= g;
                        --g;
                        ++rg;
                    } else {
                        r++;
                    }
                    break;
                }
                case 'B': {
                    if (rg > 0) {
                        ans *= rg;
                        --rg;
                    } else if (r > 0) {
                        ans *= r;
                        --r;
                        ++br;
                    } else if (g > 0) {
                        ans *= g;
                        --g;
                        ++bg;
                    } else {
                        b++;
                    }
                    break;
                }
                case 'G': {
                    if (br > 0) {
                        ans *= br;
                        --br;
                    } else if (b > 0) {
                        ans *= b;
                        --b;
                        ++bg;
                    } else if (r > 0) {
                        ans *= r;
                        --r;
                        ++rg;
                    } else {
                        g++;
                    }
                    break;
                }
            }
        }
 
        for (int i = 1; i <= N; ++i) {
            ans *= i;
        }
        cout << ans << endl;
    }
};
