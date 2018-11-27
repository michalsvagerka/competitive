#include "../l/lib.h"
// #include "../l/mod.h"

class TaskF {
public:
    void solve(istream& cin, ostream& cout) {
        vector<double> PW(101, 1);
        for (int i = 0; i < 100; ++i) PW[i+1] = PW[i] / 0.9;

        int TC; cin >> TC;
        for (int tc = 0; tc < TC; ++tc) {
            int N; cin >> N;
            double C, T; cin >> C >> T;
            vector<pii> P(N); cin >> P;
            sort(P.begin(), P.end());
            reverse(P.begin(), P.end());

            vector2<double> M(N+1, 10*N+1, 1e80);
            M[0][0] = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = i; j >= 0; --j) {
                    for (int k = 0; k <= 10*j; ++k) {
                        M[j+1][k+P[i].y] = min(M[j+1][k+P[i].y], M[j][k] + P[i].x * PW[j+1]);
                    }
                }
            }

            int ans = 0;
            for (int i = 1; i <= N; ++i) {
                for (int j = 10*i; j >= i; --j) {
                    double tt = M[i][j];
                    double topt = (sqrt(C * tt) - 1) / C;
                    if (topt < 1e-20) topt = 0;
                    if (topt > T) continue;
                    double tot = topt + tt / (1 + C * topt) + i * 10;
                    if (tot <= T) {
                        ans = max(ans, j); break;
                    }
                }
            }
            cout << ans << '\n';
        }
    }
};
