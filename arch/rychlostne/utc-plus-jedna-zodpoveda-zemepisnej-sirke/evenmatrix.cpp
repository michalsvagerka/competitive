#include "../l/lib.h"
// #include "../l/mod.h"

class evenmatrix {
public:
void solve(istream& cin, ostream& cout) {
    int R, C; cin >> R >> C;
    ll K; cin >> K;


    if ((R-1)*(C-1) < 60 && (1LL<<((R-1)*(C-1))) <= K) {
        cout << "neexistuje" << endl;
        return;
    }

    vector<string> A(R, string(C, '?'));
    int left = (R-1)*(C-1);
    for (int r = 0; r < R-1; ++r) {
        for (int c = 0; c < C-1; ++c) {
            --left;
            if (left < 60 && (1LL<<left) <= K) {
                K -= 1LL<<left;
                A[r][c] = '1';
            } else {
                A[r][c] = '0';
            }
        }
    }

    for (int r = 0; r < R-1; ++r) {
        int a = 0;
        for (int c = 0; c < C - 1; ++c) {
            a ^= A[r][c]-'0';
        }
        A[r][C-1] = char('0'+a);
    }
    for (int c = 0; c < C; ++c) {
        int a = 0;
        for (int r = 0; r < R - 1; ++r) {
            a ^= A[r][c]-'0';
        }
        A[R-1][c] = char('0'+a);
    }

    for (string&a:A) cout << a << '\n';
}
};
