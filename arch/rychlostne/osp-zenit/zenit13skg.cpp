#include "../l/lib.h"

class zenit13skg {
public:
    void fill(vector<string>& A, int R, int C, int r, int c) {
        if (r < 0 || r >= R || c < 0 || c >= C) return;
        if (A[r][c] == '#') {
            A[r][c] = '*';
            fill(A,R,C,r+1,c);
            fill(A,R,C,r-1,c);
            fill(A,R,C,r,c+1);
            fill(A,R,C,r,c-1);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int R, C; cin >> R >> C;
        vector<string> A(R); cin >> A;
        fill(A, R, C, 0, 0);
        int ans = 0;
        for (int i = 0; i < R; ++i) {
            ans += count(A[i].begin(),A[i].end(),'#');
        }
        cout << ans << '\n';
    }
};
