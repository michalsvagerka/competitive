#include "../l/lib.h"

class zenit14ckj {
public:
    void solve(istream& cin, ostream& cout) {
        int R, C; cin >> R >> C;
        vector<string> A(R); cin >> A;
        vector<int> X(1<<(2*C), 1000);
        for (int i = 0; i < (1<<(2*C)); ++i) {
            bool ok = true;
            int cnt = 0;
            for (int j = 0; j < 2 && ok; ++j) {
                for (int k = 0; k < C && ok; ++k) {
                    if (A[j][k] == 'X') {
                        if ((i&1<<(j*C+k)) != 0) ok = false;
                    } else {
                        cnt += ((i&1<<(j*C+k)) != 0);
                        if (k >= 2) {
                            if (((i&1<<(j*C+k-2)) == 0) && ((i&1<<(j*C+k-1)) == 0) && ((i&1<<(j*C+k)) == 0)
                                && A[j][k-2] == '.' && A[j][k-1] == '.' && A[j][k] == '.') ok = false;
                        }
                    }
                }
            }
            if (ok) X[i] = cnt;
        }

        for (int i = 2; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                vector<int> Y(1<<(2*C), 1000);
                for (int m = 0; m < (1<<(2*C)); ++m) {
                    if (X[m] == 1000) continue;
                    bool canZero = true, canOne = true;
                    if (A[i-2][j] == '.' && A[i-1][j] == '.' && A[i][j] == '.' && (m&1) == 0 && (m&1<<C) == 0) {
                        canZero = false;
                    }
                    if (j >= 2 && A[i][j-2] == '.' && A[i][j-1] == '.' && A[i][j] == '.' && (m&1<<(2*C-2)) == 0 && (m&1<<(2*C-1)) == 0) {
                        canZero = false;
                    }
                    if (A[i][j] == 'X') canOne = false;
                    if (canZero) Y[m>>1] = min(Y[m>>1], X[m]);
                    if (canOne) Y[m>>1|(1<<(2*C-1))] = min(Y[m>>1|(1<<(2*C-1))], X[m]+1);
                }
                swap(X,Y);
            }
        }

        cout << *min_element(X.begin(),X.end()) << '\n';

    }
};
