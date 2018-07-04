#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<pii> P(N); cin >> P;

    constexpr int thrd = 100;
    double over = N > thrd ? 0 : pow(2,-N);
    double tot = ll(N)*(N-1)/2 + N + 1;
    tot *= over;

    double ans = 0;
    for (int i = 0; i < N; ++i) {
        ll x1 = P[i].x;
        ll y1 = P[i].y;
        for (int j = 1; j < min(thrd,N); ++j) {
            ll x2 = P[(i+j)%N].x;
            ll y2 = P[(i+j)%N].y;
            double cnt = pow(2,-j-1);
            if (N <= thrd) cnt = (cnt - over) / (1 - tot);
            int dx = x1-x2;
            int dy = y1-y2;
            int g;
            if (dy == 0) {
                g = abs(dx);
            } else if (dx == 0) {
                g = abs(dy);
            } else {
                g = gcd(abs(dx), abs(dy));
            }
            ans += (x1 * y2 - x2 * y1 - g) * cnt;
        }
    }

    cout << fixed << setprecision(20) << ans/2 + 1 << endl;
}
};
