#include "../l/lib.h"
#include "../l/mod.h"

//typedef double FF;
typedef Field<998244353> FF;

class TradeForTriples {
public:
    int findExpectation(int N, int K, int A, int B) {
        vector<FF> Inv(N*K+1);
        for (int i = 1; i <= N*K; ++i) {
            Inv[i] = FF{1} / FF(i);
        }

        vector2<FF> E(K+1, K+1, 1);
        for (int b = K; b >= 0; b--) {
            for (int a = K-b; a >= 0; --a) {
                vector2<FF> H(K+1, K+1, 0);
                H[a][b] = 1;
                FF keep = 0;
                for (int d = 0; d <= K; ++d) {
                    for (int c = 0; c+d <= K; c++) {
                        if (c+2*d == a+2*b+A) {
                            int newC = c;
                            int newD = d;
                            while (2*newD > B) { --newD; ++newC; }
                            while (newC + 2*newD > B) { --newC; }
                            if (newC == a && newD == b) {
                                keep += H[c][d];
                            } else {
                                E[a][b] += H[c][d] * E[newC][newD];
                            }
                        } else {
                            FF prob = H[c][d] * Inv[N*K-c-2*d];
                            if (c + d != K) H[c + 1][d] += N * (K - c - d) * prob;
                            if (c != 0) H[c - 1][d + 1] += (N - 1) * c * prob;
                        }
                    }
                }

                E[a][b] /= 1-keep;
            }
        }

        return (ui)E[0][0];
    }

    void solve(istream& cin, ostream& cout) {
        cout << findExpectation(3,1,1,2) << endl;
        cout << findExpectation(3,2,1,2) << endl;
        cout << findExpectation(7,1,2,1) << endl;
        cout << findExpectation(29, 15, 5, 9) << endl;
        cout << findExpectation(50, 50, 99, 75) << endl;
        cout << findExpectation(50, 50, 2, 1) << endl;
    }
};
