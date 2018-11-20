#include "../l/lib.h"
// #include "../l/mod.h"

class lovmysi {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> X(N+1, 0), Y(N+1, 0), T(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> X[i] >> Y[i] >> T[i];
    }
    double M; cin >> M;

    vector2<double> Dist(N+1, N+1);
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            Dist[i][j] = sqrt(pow(X[j] - X[i], 2) + pow(Y[j] - Y[i], 2));
        }
    }
    vector2<double> D(1<<N, N+1, 1e10);
    double ans = bsld(1e-4, 1e10, [&](double start) {
        for (int i = 0; i < (1<<N); ++i) {
            for (int j = 0; j <= N; ++j) {
                D[i][j] = 1e10;
            }
        }
        
        D[0][0] = 0;
        for (int i = 0; i < (1<<N); ++i) {
            double speed = start * pow(M, __builtin_popcount(i));
            for (int k = 0; k <= N; ++k) {
                if (D[i][k] > 1e8) continue;
                for (int j = 0; j < N; ++j) {
                    if (i & (1 << j)) continue;
                    double dist = Dist[j+1][k];
                    double time = dist / speed;
                    if (D[i][k] + time <= T[j+1]) {
                        D[i|(1<<j)][j+1] = min(D[i|(1<<j)][j+1], D[i][k] + time);
                    }
                }
            }
        }

        double t = 1e10;
        for (int j = 0; j < N; ++j) t = min(t, D[(1<<N)-1][j+1]);
        return t < 1e6;
    });

    cout << fixed << setprecision(12) << ans << endl;
}
};
