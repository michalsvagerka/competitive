#include "../l/lib.h"

class BBeingawesomeism {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int R, C; cin >> R >> C;
            vector<string> A(R); cin >> A;
            bool hasA = false, hasP = false;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (A[r][c] == 'A') hasA = true;
                    else hasP = true;
                }
            }
            if (!hasA) {
                cout << "MORTAL\n"; continue;
            }
            if (!hasP) {
                cout << 0 << '\n'; continue;
            }

            int ans = 4;

            bool firstRow = true, lastRow = true, firstColumn = true, lastColumn = true;
            bool border = false;
            for (int r = 0; r < R; ++r) {
                firstColumn &= A[r][0] == 'A';
                lastColumn &= A[r][C-1] == 'A';
                border |= A[r][0] == 'A';
                border |= A[r][C-1] == 'A';
            }
            for (int c = 0; c < C; ++c) {
                firstRow &= A[0][c] == 'A';
                lastRow &= A[R-1][c] == 'A';

                border |= A[0][c] == 'A';
                border |= A[R-1][c] == 'A';
            }
            if (firstRow || lastRow || firstColumn || lastColumn) {
                cout << 1 << '\n';
                continue;
            }
            if (A[0][0] == 'A' || A[0][C-1] == 'A' || A[R-1][0] == 'A' || A[R-1][C-1] == 'A') {
                cout << 2 << '\n';
                continue;
            }

            if (border) ans = 3;
            
            for (int r = 0; r < R; ++r) {
                bool col = true;
                for (int c = 0; c < C; ++c) {
                    col &= A[r][c] == 'A';
                }
                if (col) ans = 2;
            }
            for (int c = 0; c < C; ++c) {
                bool row = true;
                for (int r = 0; r < R; ++r) {
                    row &= A[r][c] == 'A';
                }
                if (row) ans = 2;
            }

//            for (int i = 0; i < 2; ++i) {
//                vector<int> Bot(C, 0), Top(C, 0);
//                for (int c = 0; c < C; ++c) {
//                    while (Bot[c] < C && A[R - 1 - Bot[c]][c] == 'A') ++Bot[c];
//                    while (Top[c] < C && A[Top[c]][c] == 'A') ++Top[c];
//                }
//                for (int c = 1; c < C; ++c) {
//                    Bot[c] = max(Bot[c], Bot[c - 1]);
//                    Top[C - 1 - c] = max(Top[C - 1 - c], Top[C - c]);
//                }
//                
//                for (int i = 0; i < C; ++i) {
//                    if (Bot[i] + Top[i] >= R) ans = 2;
//                }
//                
//                if (i==1) {
//                    vector<string> W(C, string(R, ' '));
//                    for (int r = 0; r < R; ++r) {
//                        for (int c = 0; c < C; ++c) {
//                            W[c][r] = A[r][c];
//                        }
//                    }
//                    swap(R, C);
//                    swap(W, A);
//                } else {
//                    for (auto&a: A) reverse(a.begin(),a.end());
//                }
//            }

            cout << ans << '\n';
        }
    }
};
