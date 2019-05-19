#include "../l/lib.h"

class BThreeReligions {
public:
    void solve(istream& cin, ostream& cout) {
        int X[251][251][251];
        int N, Q; cin >> N >> Q;
        string S; cin >> S;
        X[0][0][0] = 0;
        vector<vector<int>> D(N+2);
        vector<int> T(26, N);
        D[N] = D[N+1] = T;
        for (int i = N-1; i >= 0; --i) {
            T[S[i]-'a'] = i;
            D[i] = T;
        }
        
        string A, B, C;

        auto upd = [&](int a, int b, int c) {
            X[a][b][c] = N+1;
            if (a > 0) {
                X[a][b][c] = min(X[a][b][c], D[X[a-1][b][c]][A[a-1]-'a']+1);
            }

            if (b > 0) {
                X[a][b][c] = min(X[a][b][c], D[X[a][b-1][c]][B[b-1]-'a']+1);
            }

            if (c > 0) {
                X[a][b][c] = min(X[a][b][c], D[X[a][b][c-1]][C[c-1]-'a']+1);
            }

        };

        vector<int> L(3, 0);
        for (int q = 0; q < Q; ++q) {
            char t; cin >> t;
            int r; cin >> r; --r;
            if (t == '+') {
                char x; cin >> x;
                L[r]++;
                if (r == 0) {
                    A.push_back(x);
                    for (int i = 0; i <= L[1]; ++i) {
                        for (int j = 0; j <= L[2]; ++j) {
                            upd(L[r], i, j);
                        }
                    }
                } else if (r == 1) {
                    B.push_back(x);
                    for (int i = 0; i <= L[0]; ++i) {
                        for (int j = 0; j <= L[2]; ++j) {
                            upd(i, L[r], j);
                        }
                    }
                } else if (r == 2) {
                    C.push_back(x);
                    for (int i = 0; i <= L[0]; ++i) {
                        for (int j = 0; j <= L[1]; ++j) {
                            upd(i, j, L[r]);
                        }
                    }
                }
            } else {
                L[r]--;
                if (r == 0) {
                    A.pop_back();
                } else if (r == 1) {
                    B.pop_back();
                } else C.pop_back();
            }

            cout << (X[L[0]][L[1]][L[2]] <= N ? "YES" : "NO") << '\n';
        }


    }
};
