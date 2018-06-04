#include "../../../l/lib.h"
// #include "../l/mod.h"

class arthurandwalls {
public:
    int R, C;
    vector<string> S;

    void fix(int r, int c) {
        if (r < 0 || r >= R-1 || c < 0 || c >= C-1) return;
        int x = (S[r][c]=='.')+(S[r+1][c]=='.')+(S[r][c+1]=='.')+(S[r+1][c+1]=='.');
        if (x == 3) {
            if (S[r][c] == '*') {
                S[r][c] = '.';
                fix(r-1,c-1);
                fix(r-1,c);
                fix(r,c-1);
            } else if (S[r][c+1] == '*') {
                S[r][c+1] = '.';
                fix(r-1,c);
                fix(r-1,c+1);
                fix(r,c+1);
            } else if (S[r+1][c] == '*') {
                S[r+1][c] = '.';
                fix(r,c-1);
                fix(r+1,c-1);
                fix(r+1,c);
            } else {
                S[r+1][c+1] = '.';
                fix(r+1,c);
                fix(r+1,c+1);
                fix(r,c+1);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> R >> C;
        S.resize(R); cin >> S;
        for (int r = 0; r < R-1; ++r) {
            for (int c = 0; c < C-1; ++c) {
                fix(r,c);
            }
        }
        for (string&s:S) cout << s << '\n';
    }
};
