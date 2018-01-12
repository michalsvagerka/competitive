#include "../l/lib.h"
#include "../l/geo.h"

class maxtri {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pll> P(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i].x >> P[i].y;
        }
        vector2<bitset<300>> D(N,N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i==j) continue;
                for (int k = 0; k < N; ++k) {
                    D[i][j][k] = ccw(P[i], P[j], P[k]) >= 0;
                }
            }
        }

        ui ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (ccw(P[i],P[j],P[k]) != 0) {
                        ui c = (D[i][j] & D[j][k] & D[k][i]).count();
                        ans = max(ans, c);
                    }
                }
            }
        }
        cout << ans << endl;
    }
};
