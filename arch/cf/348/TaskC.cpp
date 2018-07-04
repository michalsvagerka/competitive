#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<long double> MX(N), MN(N), P(N), Q(N);
    cin >> MX >> MN;

    long double sA = 0, sB = 0;

    for (int i = 0; i < N; ++i) {

        long double a = -1, b = sB - sA + MX[i] + MN[i], c = (MX[i]+MN[i])*sA - MX[i];
        long double det = b*b - 4*a*c;
        if (det < 1e-20) det = 0;
        else det = sqrt(det);
        P[i] = (-b - det)/(2*a);
        Q[i] = MX[i] + MN[i] - P[i];
        sA += P[i];
        sB += Q[i];
    }

    for (auto&p:P) if (p<1e-10) p = 0;
    for (auto&q:Q) if (q<1e-10) q = 0;
    cout << fixed << setprecision(10) << P << Q;
}
};
