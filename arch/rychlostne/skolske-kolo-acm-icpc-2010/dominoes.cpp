#include "../l/lib.h"
// #include "../l/mod.h"

class dominoes {
public:
    void solve(istream& cin, ostream& cout) {
        int R,C,r,c; cin >> R >> C >> r >> c;
        if (R % 2 == 0 || C % 2 == 0 || r%2 != c%2) {
            cout << "impossible\n";
        } else {
            --r; --c;
            vector<string> A(R,string(C,' '));
            for (int a = 0; a < r-1; a+=2) {
                for (int b = 0; b < C; ++b) {
                    A[a][b] = A[a+1][b] = "abcd"[a&2|b&1];
                }
            }
            for (int a = 1+r+(r&1); a < R-1; a+=2) {
                for (int b = 0; b < C; ++b) {
                    A[a][b] = A[a+1][b] = "abcd"[a&2|b&1];
                }
            }
            for (int a = r - (r&1); a <= r+(r&1); ++a) {
                for (int b = 0; b < c-1; b += 2) {
                    A[a][b] = A[a][b + 1] = "efgh"[a&1|b&2];
                }
                for (int b = c+1+(c&1); b < C; b += 2) {
                    A[a][b] = A[a][b + 1] = "efgh"[a&1|b&2];
                }
            }
            if (r&1) {
                A[r-1][c-1] = A[r-1][c] = 'i';
                A[r-1][c+1] = A[r][c+1] = 'j';
                A[r+1][c+1] = A[r+1][c] = 'k';
                A[r+1][c-1] = A[r][c-1] = 'l';
            }
            A[r][c] = '*';
            for (auto &a:A) cout << a << '\n';
        }

    }
};
