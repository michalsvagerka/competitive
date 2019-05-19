#include "../l/lib.h"

typedef unsigned char uc;
uc D[186][186][186][18];

class DComplexity {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W; cin >> H >> W;
        vector<string> A(H); cin >> A;
        vector2<int> P(H+1, W+1, 0);
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                P[i+1][j+1] = P[i+1][j] + P[i][j+1] - P[i][j] + (A[i][j] == '#');
            }
        }

        auto get = [&](int h1, int w1, int h2, int w2) {
            return P[h2+1][w2+1] - P[h2+1][w1] - P[h1][w2+1] + P[h1][w1];
        };

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                for (int k = j; k < W; ++k) {
                    int s = bsh(i, H-1, [&](int x) { int y = get(i, j, x, k); return y == 0 || y == (x-i+1)*(k-j+1); });
                    if (s == -1) {
                        D[i][j][k][0] = 0;
                    } else {
                        D[i][j][k][0] = s - i + 1;
                    }
                }
            }
        }

        for (int l = 1; l <= 17; ++l) {
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
                    for (int k = j; k < W; ++k) {
                        uc r = D[i][j][k][l-1];
                        if (i+r != H) {
                            D[i][j][k][l] = max(D[i][j][k][l], uc(r + D[i+r][j][k][l-1]));
                        } else {
                            D[i][j][k][l] = max(D[i][j][k][l], r);
                        }

                        if (k!=W-1) {
                            // go right
                            int t = bsh(k+1, W-1, [&](int x) { return D[i][k+1][x][l-1] >= r; });
                            if (t != -1) {
                                D[i][j][t][l] = max(D[i][j][t][l], r);
                            }
                        }
                        if (j != 0) {
                            // go left
                            int t = bsl(0, j-1, [&](int x) { return D[i][x][j-1][l-1] >= r; });
                            if (t != -1) {
                                D[i][t][k][l] = max(D[i][t][k][l], r);
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < H; ++i) {
                for (int len = H; len >= 2; --len) {
                    for (int j = 0; j + len <= H; ++j) {
                        int k = j + len - 1;
                        D[i][j][k-1][l] = max(D[i][j][k-1][l], D[i][j][k][l]);
                        D[i][j+1][k][l] = max(D[i][j+1][k][l], D[i][j][k][l]);
                    }
                }
            }
        }

        for (int l = 0; l <= 16; ++l) {
            if (D[0][0][W-1][l] == H) {
                cout << l << endl;
                return;
            }
        }
    }
};
