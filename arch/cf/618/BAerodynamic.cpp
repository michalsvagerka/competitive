#include "../l/lib.h"

class BAerodynamic {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N%2 == 1) {
            cout << "NO\n";
            return;
        }
        vector<pii> P(N); cin >> P;
        N /= 2;
        pii x = {P[0].x + P[N].x, P[0].y + P[N].y};
        for (int i = 0; i < N; ++i) {
            if (P[i].x + P[i+N].x != x.x || P[i].y + P[i+N].y != x.y) {
                cout << "NO\n";
                return;
            }
        }

        cout << "YES\n";
    }
};
