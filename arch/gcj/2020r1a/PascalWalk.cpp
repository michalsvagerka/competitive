#include "../l/lib.h"

class PascalWalk {
public:
    vector<vector<int>> C;
    vector<pii> res;
    bool solve(int N, int r, int c) {
        if (res.size() > 90) return false;
        if (C[r-1][c-1] == -1) return false;
        N -= C[r-1][c-1];
        if (N == 0) return true;
        if (N < 0) return false;

        res.push_back({r+1,c+1});
        if (solve(N, r+1, c+1)) return true;
        res.pop_back();

        res.push_back({r+1,c});
        if (solve(N, r+1, c)) return true;
        res.pop_back();

        if (c != 1) {
            res.push_back({r, c - 1});
            if (solve(N, r, c - 1)) return true;
            res.pop_back();
        }

        return false;
    }

    void solve(istream& cin, ostream& cout) {
        C = vector2<int>(500, 500, -1);
        for (int i = 0; i < 500; ++i) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < min(i,8); ++j) {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
                if (C[i][j] > 1000000000) C[i][j] = -1;
            }
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            res = {{1,1}};
            cout << "Case #" << t+1 << ":\n";
            if (N >= 2) {
                res.push_back({2,1});
                if (!solve(N-1, 2, 1)) {
//                    cerr << "NO\n";
                }
            }
            for (pii x: res) cout << x << '\n';
        }
    }
};
