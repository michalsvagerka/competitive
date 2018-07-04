#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<double> P(N); cin >> P;
    sort(P.begin(),P.end());

    double ans = 0.0;
    for (int b = 0; b < N; ++b) {
        for (int e = b; e <= N; ++e) {
            vector<double> Z;
            for (int i = 0; i < b; ++i) Z.push_back(P[i]);
            for (int i = e; i < N; ++i) Z.push_back(P[i]);

            vector2<double> D(Z.size()+1, 2, 0);
            D[0][0] = 1;
            for (int i = 0; i < Z.size(); ++i) {
                D[i+1][0] = D[i][0] * (1-Z[i]);
                D[i+1][1] = D[i][0] * Z[i] + D[i][1] * (1-Z[i]);
            }
            ans = max(ans, D.back().back());
        }
    }
    cout << fixed << setprecision(12) << ans << endl;
}
};
