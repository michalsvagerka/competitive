#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int R, C; cin >> R >> C;
    vector<string> S(R); cin >> S;
    vector<string> A = S;

    auto neigh = [&](int r, int c) {
        int ans = 0;
        if (r > 0) ans += A[r-1][c] == '.';
        if (r < R - 1) ans += A[r+1][c] == '.';
        if (c > 0) ans += A[r][c-1] == '.';
        if (c < C-1) ans += A[r][c+1] == '.';
        return ans;
    };

    vector<pii> Q;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (A[r][c] == '.') {
                if (neigh(r, c) == 1) {
                    Q.push_back({r,c});
                }
            }
        }
    }

    auto check = [&](int r, int c) {
        if (r > 0 && neigh(r-1,c) == 1) Q.push_back({r-1,c});
        if (r < R-1 && neigh(r+1,c) == 1) Q.push_back({r+1,c});
        if (c > 0 && neigh(r,c-1) == 1) Q.push_back({r,c-1});
        if (c < C-1 && neigh(r,c+1) == 1) Q.push_back({r,c+1});
    };

    for (int i = 0; i < Q.size(); ++i) {
        int r = Q[i].x, c = Q[i].y;
        if (A[r][c] != '.') continue;
        if (r > 0 && A[r-1][c] == '.') { A[r-1][c] = '^'; A[r][c] = 'v'; check(r-1, c); }
        if (r < R-1 && A[r+1][c] == '.') { A[r][c] = '^'; A[r+1][c] = 'v'; check(r+1, c); }
        if (c > 0 && A[r][c-1] == '.') { A[r][c-1] = '<'; A[r][c] = '>'; check(r, c-1); }
        if (c < C-1 && A[r][c+1] == '.') { A[r][c] = '<'; A[r][c+1] = '>'; check(r, c+1); }
    }

    for (string&a:A) {
        if (count(a.begin(),a.end(),'.')) {
            cout << "Not unique\n";
            return;
        }
    }

    for (string&a:A) cout << a << '\n';

}
};
