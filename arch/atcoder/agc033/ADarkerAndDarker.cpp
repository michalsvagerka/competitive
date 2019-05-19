#include "../l/lib.h"

class ADarkerAndDarker {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W; cin >> H >> W;
        vector<string> S(H); cin >> S;
        vector2<int> D(H, W, 1e8);
        vector<pii> Q;
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                if (S[h][w] == '#') {
                    Q.push_back({h,w});
                    D[h][w] = 0;
                }
            }
        }

        int ans = 0;
        for (int q = 0; q < H*W; ++q) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (abs(dx)+abs(dy) != 1) continue;
                    int h = Q[q].x + dx;
                    int w = Q[q].y + dy;
                    if (h >= 0 && h < H && w >= 0 && w < W && S[h][w] == '.') {
                        D[h][w] = D[Q[q].x][Q[q].y] + 1;
                        Q.push_back({h,w});
                        ans = D[h][w];
                        S[h][w] = '#';
                    }
                }
            }
        }

        cout << ans << '\n';
    }
};
