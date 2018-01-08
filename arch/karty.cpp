#include "../l/lib.h"
// #include "../l/mod.h"

class karty {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector4<double> DP(N+1, N+1, 2, 2, 0.0);
        for (int r = 0; r <= N; ++r) {
            for (int b = 0; b <= N; ++b) {
                for (int c = 0; c < 2; ++c) {
                    for (int j = 0; j < 2; ++j) {
                        int t = r+b+c+j;
                        if (t == 0) continue;
                        double ans = 0.0;
                        if (r) ans += r*(DP[r-1][b][c][j]+1);
                        if (b) ans += b*(DP[r][b-1][c][j]-1);
                        if (j) ans += DP[r][b][c][j-1]+5;
                        if (c) ans += DP[r][b][c-1][j]-5;
                        DP[r][b][c][j] = max(ans / t, 0.0);
                    }
                }
            }
        }
        cout << fixed << setprecision(10) << DP[N][N][1][1] << endl;
    }
};

