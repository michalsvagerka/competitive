#include "../../../l/lib.h"

class CStrawberryCakes {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W, K; cin >> H >> W >> K;
        vector<string> S(H); cin >> S;
        vector2<int> Ans(H, W, -1);
        int s = 0;
        for (int i = 0; i < H; ++i) {
            bool is = false;
            for (int j = 0; j < W; ++j) {
                is |= S[i][j] == '#';
            }
            if (is) {
                for (int j = 0; j < W; ++j) {
                    if (S[i][j] == '#') {
                        ++s;
                    }
                    Ans[i][j] = s;
                }
                for (int j = 0; j < W; ++j) {
                    if (S[i][j] == '#') break;
                    Ans[i][j]++;
                }
            }
        }

        for (int t = 0; t < H; ++t) {
            for (int i = 0; i < H; ++i) {
                if (Ans[i][0] == -1) {
                    if (i != H-1 && Ans[i+1][0] != -1) {
                        Ans[i] = Ans[i+1];
                    }
                    if (i != 0 && Ans[i-1][0] != -1) Ans[i] = Ans[i-1];
                }
            }
        }

        cout << Ans;
    }
};
