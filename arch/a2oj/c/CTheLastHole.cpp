#include "../l/lib.h"
#include "../l/geo.h"

class CTheLastHole {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

        vector<Point<ll>> P(N); cin >> P;
        vector<Point<double>> R(N);
        for (int i = 0; i < N; ++i) {
            R[i] = {(double)P[i].x, (double)P[i].y};
        }
        auto right_angle = [&](int i, int j, int k) {
            ll a = P[i].squaredDistance(P[j]);
            ll b = P[i].squaredDistance(P[k]);
            ll c = P[k].squaredDistance(P[j]);
            ll d = max(a, max(b, c));
            return 2*d == a + b + c;
        };

        double ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    if (right_angle(i, j, k)) {
                        for (int l = k+1; l < N; ++l) {
                            if (right_angle(i, j, l) && right_angle(i, k, l) && right_angle(j, k, l)) {
                                Circle<double> C(R[i], R[j], R[k]);
                                bool del = true;
                                for (int m = 0; m < N; ++m) {
                                    del &= C.center.squaredDistance(R[m]) >= C.sqRadius - 1e-6;
                                }
                                if (del) ans = max(ans, C.sqRadius);
                            }
                        }
                    } else {
                        ll a = P[i].squaredDistance(P[j]);
                        ll b = P[i].squaredDistance(P[k]);
                        ll c = P[k].squaredDistance(P[j]);
                        ll d = max(a, max(b, c));
                        if (2 * d < a + b + c) {
                            Circle<double> C(R[i], R[j], R[k]);
                            bool del = true;
                            for (int l = 0; l < N; ++l) {
                                del &= C.center.squaredDistance(R[l]) >= C.sqRadius - 1e-6;
                            }
                            if (del) ans = max(ans, C.sqRadius);
                        }
                    }
                }
            }
        }

        if (ans < 1e-6) cout << -1 << endl;
        else cout << fixed << setprecision(8) << sqrt(ans) << endl;
    }
};
