#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, K;
    cin >> N >> K;

    int s = 1000;
    vector<double> D(N+1, 0), E = D;

    double KK = 1.0/K;

    E[0] = 1;
    double ans = 0;
    for (int l = 1; l < s; ++l) {
        double z = ((K-1) + l / double(l+1));
        double y = 1.0/l;
        for (int t = 0; t <= min(N,l-2); ++t) E[t] = 0;
        for (int t = 1; t <= N; ++t) {
            if (t <= l - 2) { continue; }
            E[t] = KK * (E[t-1] * z + D[t-1] * y);
            if (E[t] < 1e-300) E[t] = 0;
        }

        double tt = 0;
        for (int t = 0; t < N; ++t) tt += E[t];
        ans += tt * l * (0.5 + 1.0/(l+1));
        swap(E,D);
        E[0] = 0;
    }

    cout << fixed << setprecision(10) << ans << endl;
}
};
