#include "../l/lib.h"
#include "../l/geo.h"

class fluttershy {
public:
    void solve(istream& cin, ostream& cout) {
        ui S, N;
        cin >> S >> N;
        vector<Point<ll>> X(S), Y(N);
        cin >> X >> Y;
        vector2<bitset<500>> W(S, S);
        for (ui i = 0; i < S; ++i) {
            for (ui j = i + 1; j < S; ++j) {
                for (ui k = 0; k < N; ++k) {
                    if (orientation(X[i], X[j], Y[k]) == 1) {
                        W[i][j][k] = true;
                    } else {
                        W[j][i][k] = true;
                    }
                }
            }
        }

        ui ans = 0;
        for (ui i = 0; i < S; ++i) {
            for (ui j = i+1; j < S; ++j) {
                if (i==j) continue;
                for (ui k = j+1; k < S; ++k) {
                    if (k==i || k==j) continue;
                    if (orientation(X[i],X[j],X[k]) == 1) {
                        ans += (W[i][j] & W[j][k] & W[k][i]).none();
                    } else {
                        ans += (W[i][k] & W[k][j] & W[j][i]).none();
                    }
                }
            }
        }
        cout << ans << endl;
    }
};
