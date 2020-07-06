#include "../l/lib.h"

class ARangeFlipFindRoute {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W; cin >> H >> W;
        vector<string> A(H); cin >> A;
        vector2<int> S(H, W, 100000);
        S[0][0] = A[0][0] == '#';
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                if (h != H-1) S[h+1][w] = min(S[h+1][w], S[h][w] + (A[h][w] != A[h+1][w]));
                if (w != w-1) S[h][w+1] = min(S[h][w+1], S[h][w] + (A[h][w] != A[h][w+1]));
            }
        }
        int s = S[H-1][W-1] + (A[H-1][W-1] == '#');
        cout << s/2 << '\n';
    }
};
