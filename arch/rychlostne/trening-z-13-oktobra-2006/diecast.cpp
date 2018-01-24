#include "../l/lib.h"
// #include "../l/mod.h"

class diecast {
public:
    void solve(istream& cin, ostream& cout) {
        int R,C; cin >> R >> C;
        while (R&&C) {
            vector<string> T(R); cin >> T;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (T[r][c] == 'X') {
                        vector<pii> Z{{r,c}};
                        for (int i = 0; i < Z.size(); ++i) {
                            int rr = Z[i].x, cc = Z[i].y;
                            if (rr < 0 || rr >= R || cc < 0 || cc >= C || T[rr][cc] != 'X') continue;
                            T[rr][cc] = "*Y"[i==0];
                            Z.push_back({rr-1,cc});
                            Z.push_back({rr+1,cc});
                            Z.push_back({rr,cc-1});
                            Z.push_back({rr,cc+1});
                        }
                    }
                }
            }

            vector<int> W;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (T[r][c] != '.') {
                        int t = 0;
                        vector<pii> Z{{r,c}};
                        for (int i = 0; i < Z.size(); ++i) {
                            int rr = Z[i].x, cc = Z[i].y;
                            if (rr < 0 || rr >= R || cc < 0 || cc >= C || T[rr][cc] == '.') continue;
                            t += (T[rr][cc] == 'Y');
                            T[rr][cc] = '.';
                            Z.push_back({rr-1,cc});
                            Z.push_back({rr+1,cc});
                            Z.push_back({rr,cc-1});
                            Z.push_back({rr,cc+1});
                        }
                        W.push_back(t);
                    }
                }
            }
            sort(W.begin(),W.end());
            cout << "Throw: " << W;

            cin >> R >> C;
        }
    }
};
