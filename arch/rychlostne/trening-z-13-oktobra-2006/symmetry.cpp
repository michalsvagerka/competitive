#include "../l/lib.h"
// #include "../l/mod.h"

class symmetry {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while (N) {
            vector<pii> P(N);
            for (int i = 0; i < N; ++i) cin >> P[i].x >> P[i].y;
            sort(P.begin(),P.end());
            bool ok = true;
            for (int i = 1; i <= N/2; ++i) ok &= (P[0].x + P[N-1].x == P[i].x + P[N-1-i].x) && (P[0].y + P[N-1].y == P[i].y + P[N-1-i].y);
            if (ok) {
                cout << "V.I.P. should stay at (" << (P[0].x + P[N-1].x)/2 << '.' << abs(5*(P[0].x + P[N-1].x)%10) << ',' << (P[0].y + P[N-1].y)/2 << '.' << abs(5*(P[0].y + P[N-1].y)%10) <<").\n";
            } else {
                cout << "This is a dangerous situation!\n";
            }
            cin >> N;
        }
    }
};
