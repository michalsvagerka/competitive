#include "../l/lib.h"

int D[51][51][50][50];

class DRectanglePainting1 {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> A(N); cin >> A;

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                for (int k = 0; k < N; ++k) {
                    for (int l = 0; l < N; ++l) {
                        D[i][j][k][l] = N;
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                D[1][1][i][j] = A[i][j] == '#';
            }
        }

        for (int w = 1; w <= N; ++w) {
            for (int h = 1; h <= N; ++h) {
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        for (int m = 1; m < w; ++m) {
                            D[w][h][i][j] = min(D[w][h][i][j], D[m][h][i][j] + D[w-m][h][i+m][j]);
                        }
                        for (int m = 1; m < h; ++m) {
                            D[w][h][i][j] = min(D[w][h][i][j], D[w][m][i][j] + D[w][h-m][i][j+m]);
                        }
                        D[w][h][i][j] = min(D[w][h][i][j], max(w,h));
                    }
                }
            }
        }
        
               
        cout << D[N][N][0][0] << '\n';
    }
};
