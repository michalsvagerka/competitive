#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int R, C; cin >> R >> C;
    vector<string> S(R); cin >> S;
    pii beg, end;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (S[r][c] == 'S') beg = {r,c};
            if (S[r][c] == 'E') end = {r,c};
        }
    }

    int infty = 1e9;
    vector2<int> D(R, C, infty);
    vector<pii> Q{end};
    D[end.x][end.y] = 0;
    while (!Q.empty()) {
        vector<pii> P;
        for (pii q:Q) {
            int r = q.x;
            int c = q.y;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if ((dr == 0) ^ (dc == 0)) {
                        int rr = r + dr;
                        int cc = c + dc;
                        if (in(0,rr,R) && in(0,cc,C) && S[rr][cc] != 'T' && D[rr][cc] == infty) {
                            D[rr][cc] = D[r][c] + 1;
                            P.push_back({rr,cc});
                        }
                    }
                }
            }
        }
        swap(P,Q);
    }

    int ans = 0;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (D[r][c] <= D[beg.x][beg.y] && S[r][c] != 'E' && S[r][c] != 'S') {
                ans += S[r][c] - '0';
            }
        }
    }
    cout << ans << endl;
}
};
