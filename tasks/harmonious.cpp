#include "../l/lib.h"
// #include "../l/mod.h"

class harmonious {
public:
    bool brute(vector2<bool> &A, int R, int C, int s = 0, int r = 0, int c = 0) {
        if (c == C) {
            c = 0;
            r += 1;
        }
        if (r == 0) {
            A[r][c] = true;
            if (brute(A,R,C,s+1,r,c+1)) return true;
            A[r][c] = false;
            return brute(A,R,C,s,r,c+1);
        } else if (r == R) {
            if (!s) return false;
            for (int c = 0; c < C; ++c) {
                bool x = A[R-1][c];
                if (R != 1) x ^= A[R-2][c];
                if (c != 0) x ^= A[R-1][c-1];
                if (c != C-1) x ^= A[R-1][c+1];
                if (x) return false;
            }
            return true;
        } else {
            bool x = A[r-1][c];
            if (r != 1) x ^= A[r-2][c];
            if (c != 0) x ^= A[r-1][c-1];
            if (c != C-1) x ^= A[r-1][c+1];
            A[r][c] = x;
            return brute(A,R,C,s+x,r,c+1);
        }
    }

/*
 * 4 4
9 4
14 4
19 4
24 4
29 4
34 4
39 4
 8 6
17 6
26 6
35 6
 20 8
34 8
9 9
19 9
24 9
34 9
39 9
30 10
14 14
16 14
24 14
34 14
16 16
29 16
33 16
34 17
19 19
24 19
34 19
39 19
26 20 1 1 1 1 1 1 0 1 1 1 1 1 1 0 1 1 1 1 1 1
30 21 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1
 */
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        if (T == 1000) {
            for (int C = 20; C < 30; ++C) {
                for (int R = C; R <= 40; ++R) {
                    vector2<bool> A(R,C,0);
                    if (R % 2 == 1 && C % 3 == 2) {
                    } else if (R % 3 == 2 && C % 2 == 1) {
                    } else {
                        if (brute(A,R,C)) {
                            cerr << R << ' ' << C << ' ' << A[0] << endl;
                        }
                    }
                }
            }

            return;
        }

        for (int t = 0; t < T; ++t) {
            int R,C; cin >> R >> C;
            bool trans = C > R;
            if (trans) swap(R,C);
            vector2<bool> A(R,C,0);
            if (R % 2 == 1 && C % 3 == 2) {
                for (int r = 0; r < R; r+=2) {
                    for (int c = 0; c < C; c+=3) {
                        A[r][c] = A[r][c+1] = true;
                    }
                }
            } else if (R % 3 == 2 && C % 2 == 1) {
                for (int r = 0; r < R; r+=3) {
                    for (int c = 0; c < C; c+=2) {
                        A[r][c] = A[r+1][c] = true;
                    }
                }
            } else if ((C == 4 && R%5 == 4)
                    || (C == 6 && R%9 == 8)
                    || (C == 8 && R%14 == 6)
                    || (C == 9 && R%10 == 9)
                    || (C == 10 && R == 30)
                    || (C == 14 && R%10 == 4)
                    || (C == 14 && R == 16)
                    || (C == 16 && R == 16)
                    || (C == 16 && R == 29)
                    || (C == 16 && R == 33)
                    || (C == 17 && R == 34)
                    || (C == 19 && R == 19)
                    || (C == 19 && R == 24)
                    || (C == 19 && R == 34)
                    || (C == 19 && R == 39)
                    || (C == 20 && R == 26)
                    || (C == 21 && R == 30)) {
                brute(A, R, C);
            }

            if (trans) {
                vector2<bool> B = A;
                A = vector2<bool>(C,R,0);
                for (int r = 0; r < R; ++r) {
                    for (int c = 0; c < C; ++c) {
                        A[c][r] = B[r][c];
                    }
                }
            }

            for (auto&a:A) cout << a;
        }

    }
};
