#include "../../../l/lib.h"
// #include "../l/mod.h"

class namethattune {
public:
    void solve(istream& cin, ostream& cout) {
        int N, T; cin >> N >> T;
        vector<pair<double, int>> S(N);
        for (int i = 0; i < N; ++i) {
            int p, t; cin >> p >> t;
            S[i] = {p/100.0, t};
        }

        vector2<double> D(N+1, T+1, 0.0);
        D[0][0] = 1.0;

        double ans = 0;
        for (int i = 0; i < N; ++i) {
            double c = 0.0;
            double p = S[i].x;
            int t = S[i].y;
            double pt = pow(1-p, t), pt1p = p * pow(1-p, t-1);
            for (int j = 0; j <= T; ++j) {
                c *= (1-p);
                if (j > 0) c += p * D[i][j-1];
                D[i+1][j] = c;

                if (j >= t) {
                    c -= D[i][j-t] * pt1p;
                    D[i+1][j] += D[i][j-t] * pt;
                }

                ans += D[i+1][j];
            }
        }

        cout << fixed << setprecision(12) << ans << endl;
    }
};
