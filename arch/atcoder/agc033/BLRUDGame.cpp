#include "../l/lib.h"

class BLRUDGame {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W, N;
        int SR, SC;
        cin >> H >> W >> N >> SR >> SC;
        string S, T; cin >> S >> T;
        SR--; SC--;
        int r1 = 0, c1 = 0, r2 = H-1, c2 = W-1;

        for (int i = N-1; i >= 0; --i) {
            switch (T[i]) {
                case 'L':
                    c2 = min(c2+1, W-1);
                    break;
                case 'R':
                    c1 = max(c1-1, 0);
                    break;
                case 'D':
                    r1 = max(r1-1, 0);
                    break;
                case 'U':
                    r2 = min(r2+1, H-1);
                    break;
            }

            switch (S[i]) {
                case 'L':
                    c1++;
                    break;
                case 'R':
                    c2--;
                    break;
                case 'D':
                    r2--;
                    break;
                case 'U':
                    r1++;
                    break;
            }
            
            if (c1 > c2 || r1 > r2) {
                cout << "NO\n";
                return;
            }
        }

        if (SR >= r1 && SR <= r2 && SC >= c1 && SC <= c2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
