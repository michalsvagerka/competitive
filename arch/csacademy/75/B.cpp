#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    vector<string> A;
    vector2<bool> V, W;
    int R,C;

    bool dfs(int r, int c) {
        if (r == -1 || r == R || c == -1 || c == C) return true;

        if (V[r][c]) return W[r][c];
        V[r][c] = true;
        bool q;
        if (A[r][c] == 'U') q = dfs(r-1,c);
        else if (A[r][c] == 'D') q = dfs(r+1,c);
        else if (A[r][c] == 'L') q = dfs(r,c-1);
        else q = dfs(r,c+1);
        return W[r][c] = q;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> R >> C;
        A.resize(R); cin >> A;
        V = W = vector2<bool>(R,C,false);
        int ans = 0;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                ans += dfs(r,c);
            }
        }
        cout << ans << '\n';

    }
};
