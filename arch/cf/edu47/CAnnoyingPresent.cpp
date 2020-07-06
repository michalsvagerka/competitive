#include "../l/lib.h"
typedef long double ld;
class CAnnoyingPresent {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> X(M); cin >> X;
        ld a = 0, b = 0, c = 0;
        ld hi = 1.0 * N * (N-1);
        ld lo = (1.0 * (N/2) * (N/2+1) + 1.0 * ((N-1)/2) * ((N-1)/2+1));
        for (int i = 0; i < M; ++i) {
            a += X[i].x;
            if (X[i].y > 0) {
                b += X[i].y;
            } else {
                c += X[i].y;
            }
        }

        cout << fixed << setprecision(14) << a+(b*hi+c*lo)/2/N << '\n';
    }
};
