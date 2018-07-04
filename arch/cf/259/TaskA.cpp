#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> M >> N;
    vector<double> Z(M+1, 0);
    Z[M] = 1;
    for (int i = 1; i <= M; ++i) {
        Z[i] = pow(1.0*i/M, N);
    }

    for (int i = M; i >= 2; --i) {
        Z[i] -= Z[i-1];
    }

    double ans = 0;
    for (int i = 1; i <= M; ++i) {
        ans += i * Z[i];
    }
    cout << fixed << setprecision(12) << ans << endl;
}
};
