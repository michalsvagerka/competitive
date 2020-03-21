#include "../l/lib.h"

class A01Matrix {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W; cin >> H >> W;
        int A, B; cin >> A >> B;
        vector<string> X(H, string(W, '0'));
        if (A == 0) {
            for (int i = 0; i < B; ++i) {
                for (int j = 0; j < W; ++j) {
                    X[i][j] = '1';
                }
            }
        } else if (B == 0) {
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < A; ++j) {
                    X[i][j] = '1';
                }
            }
        } else {
            for (int i = 0; i < B; ++i) {
                for (int j = 0; j < A; ++j) {
                    X[i][j] = '1';
                }
            }
            for (int i = B; i < H; ++i) {
                for (int j = A; j < W; ++j) {
                    X[i][j] = '1';
                }
            }
        }

        for (string &x:X) cout << x << '\n';
    }
};
