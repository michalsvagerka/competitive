#include "../l/lib.h"
// #include "../l/mod.h"

class mikkriza {
public:
    void solve(istream& cin, ostream& cout) {
        int R,C,S;
        cin >> R >> C >> S;
        vector4<pii> Q(32,32,32,32, {0,0});
        vector2<int> D(32,32), P(33, 33, 0);
        while (R) {
            for (int i = 0; i <= 32; ++i) P[0][i] = P[i][0] = 0;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    cin >> D[r][c];
                }
            }
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; c++) {
                    P[r+1][c+1] = P[r+1][c] + P[r][c+1] - P[r][c] + D[r][c];
                }
            }

            int d = P[R][C]-S;
            for (int h = 0; h < R; ++h) {
                for (int w = 0; w < C; ++w) {
                    for (int r = 0; r+h < R; ++r) {
                        for (int c = 0; c+w < C; ++c) {
                            int t = P[r+h+1][c+w+1] + P[r][c] - P[r+h+1][c] - P[r][c+w+1];
                            Q[h][w][r][c] = (t>=d) ? pii{1,t-d} : pii{0,0};
                            for (int e = 0; e < h; ++e) {
                                Q[h][w][r][c] = max(Q[h][w][r][c], {
                                        Q[e][w][r][c].x + Q[h - e - 1][w][r + e + 1][c].x,
                                        min(Q[e][w][r][c].y, Q[h - e - 1][w][r + e + 1][c].y)
                                });
                            }
                            for (int e = 0; e < w; ++e) {
                                Q[h][w][r][c] = max(Q[h][w][r][c], {
                                        Q[h][e][r][c].x + Q[h][w-e-1][r][c+e+1].x,
                                    min(Q[h][e][r][c].y , Q[h][w-e-1][r][c+e+1].y)
                                });
                            }
                        }
                    }
                }
            }

            cout << Q[R-1][C-1][0][0].x << ' ' << Q[R-1][C-1][0][0].y << endl;

            cin >> R >> C >> S;
        }
    }
};
