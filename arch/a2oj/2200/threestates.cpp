#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int inf = 1e6;

class threestates {
public:
    void solve(istream& cin, ostream& cout) {
        int R,C; cin >> R >> C;
        vector<string> S(R); cin >> S;
        vector3<int> D(3, R, C, inf);
        vector2<int> DST(3, 3, inf);
        for (int i = 0; i < 3; ++i) {
            vector<pii> Q;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (S[r][c]-'1' == i) {
                        Q.push_back({r,c});
                        D[i][r][c] = 0;
                    }
                }
            }

            for (int q = 0; q < Q.size(); ++q) {
                int r = Q[q].x, c = Q[q].y;
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if ((dr == 0) != (dc == 0)) {
                            int rr = r + dr, cc = c + dc;
                            if (in(0,rr,R) && in(0,cc,C) && S[rr][cc] != '#' && D[i][rr][cc] == inf) {
                                D[i][rr][cc] = D[i][r][c] + 1;
                                Q.push_back({rr,cc});
                                if (in('1', S[rr][cc], '4')) {
                                    DST[i][S[rr][cc]-'1'] = min(DST[i][S[rr][cc]-'1'], D[i][rr][cc]);
                                }
                            }
                        }
                    }
                }
            }
        }


        int ans = inf;
        ans = min(ans, DST[0][1] + DST[1][2]);
        ans = min(ans, DST[0][2] + DST[1][2]);
        ans = min(ans, DST[0][1] + DST[0][2]);
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                ans = min(ans, D[0][r][c] + D[1][r][c] + D[2][r][c]);
            }
        }


        if (ans >= inf) {
            cout << "-1\n";
        } else {
            cout << ans - 2 << '\n';
        }
    }
};
