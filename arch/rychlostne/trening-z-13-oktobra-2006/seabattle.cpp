#include "../l/lib.h"
// #include "../l/mod.h"

class seabattle {
public:
    void solve(istream& cin, ostream& cout) {
        int R,C;cin >> R >> C;
        while(R&&C) {
            vector<string> T(R); cin >> T;

            int ans = 0;
            bool ok = true;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (T[r][c] == '#') {
                        int rb = r, cb = c;
                        while (rb < R && T[rb][c] == '#') ++rb;
                        while (cb < C && T[r][cb] == '#') ++cb;

                        ++ans;
                        for (int rr = r; rr < rb; ++rr) {
                            for (int cc = c; cc < cb; ++cc) {
                                ok &= T[rr][cc] == '#';
                                T[rr][cc] = '.';
                            }
                        }

                        for (int rr = r-1; rr <= rb; ++rr) {
                            for (int cc = c-1; cc <= cb; ++cc) {
                                ok &= rr < 0 || cc < 0 || rr == R || cc == C || T[rr][cc] == '.';
                            }
                        }
                    }
                }
            }

            if (ok) {
                cout << "There are " << ans << " ships.\n";
            } else {
                cout << "Bad placement.\n";
            }

            cin >> R >> C;
        }
    }
};
