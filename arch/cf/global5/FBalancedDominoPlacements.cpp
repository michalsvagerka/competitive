#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<998244353> FF;

class FBalancedDominoPlacements {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W; cin >> H >> W;
        int N; cin >> N;
        vector<bool> A(H, false);
        vector<bool> B(W, false);
        for (int i = 0; i < N; ++i) {
            int a,b,c,d; cin >> a >> b >> c >> d;
            A[a-1] = A[c-1] = B[b-1] = B[d-1] = true;
        }

        vector3<FF> X(H+1, H/2+1, 2, 0);
        X[0][0][1] = 1;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j <= H/2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (X[i][j][k] == 0) continue;
                    if (k == 0 && !A[i-1] && !A[i]) {
                        X[i+1][j+1][1] += X[i][j][k];
                    }

                    X[i+1][j][0] += X[i][j][k];
                }
            }
        }

        int freeH = count(A.begin(),A.end(),false);

        vector<FF> CNTH(H/2+1);
        for (int i = 0; i <= H/2; ++i) {
            CNTH[i] = X[H][i][0] + X[H][i][1];
        }
//
        vector3<FF> Y(W+1, W/2+1, 2, 0);
        Y[0][0][1] = 1;
        for (int i = 0; i < W; ++i) {
            for (int j = 0; j <= W/2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (Y[i][j][k] == 0) continue;
                    if (k == 0 && !B[i-1] && !B[i]) {
                        Y[i+1][j+1][1] += Y[i][j][k];
                    }

                    Y[i+1][j][0] += Y[i][j][k];
                }
            }
        }

        int freeW = count(B.begin(),B.end(),false);

        vector<FF> CNTW(W/2+1);
        for (int i = 0; i <= W/2; ++i) {
            CNTW[i] = Y[W][i][0] + Y[W][i][1];
        }

        auto F = FF::fact(10000);
        auto I = FF::invfact(10000);
        
        FF ans = 0;
        for (int i = 0; i <= H/2; ++i) {
            for (int j = 0; j <= W/2; ++j) {
                if (2*i + j > freeH || 2*j + i > freeW) continue;
                ans += CNTH[i] * CNTW[j] * F[freeW - 2*j] * I[freeW - 2*j - i]  * F[freeH - 2*i] * I[freeH - 2*i - j];
            }
        }
        cout << ans << endl;
    }
};


// .......
// .......
// AA.....
// ...BB..
// .......

//5 7 2
//3 1 3 2
//4 4 4 5