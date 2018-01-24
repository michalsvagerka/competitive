#include "../l/lib.h"
#include "../l/geo.h"

class minimaxtri {
public:
    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ui N; cin >> N;
            Polygon<ll> P(N); cin >> P;
            ll ar = P.doubleSignedArea();
            if (ar < 0) { reverse(P.begin(),P.end()); ar = -ar; }

            if (N <= 3) {
                cout << ar/2 << '.' << 5*ar%10 << '\n';
                continue;
            }

            vector2<bool> V(N,N,false);
            for (ui i = 0; i < N; ++i) {
                for (ui j = (i+2)%N; (j+1)%N != i; j=(j+1)%N) {
                    bool ok = true;
                    for (ui k = (i+1)%N; k != j && ok; k=(k+1)%N) {
                        ok &&= orientation(P[i], P[j], P[k]) == -1;
                    }
                    V[i][j] = ok;
                }
            }

            for (ui i = 0; i < N; ++i) {
                for (ui j = 0; j < N; ++j) {
                    V[i][j] = V[j][i] = V[i][j] && V[j][i];
                }
            }

            vector2<ll> D(N, N, 0);
            for (ui l = 1; l < N; ++l) {
                for (ui i = 0; i < N; ++i) {
                    ui j = (i + l + 1) % N;
                    if (V[i][j]) {
                        ui k = (i + l) % N, m = (i+1)%N;
                        D[l][i] = min(
                                max(area(P[i], P[k], P[j]), D[l-1][i]),
                                max(area(P[i], P[m], P[j]), D[l-1][m])
                        );
                    } else {
                        D[l][i] = 1e16;
                    }
                }
            }

            ll ans = 1e16;
            for (ui i = 0; i < N; ++i) {
                for (int l = 1; l < N-2; ++l) {
                    if (V[i][(i+l+1)%N]) {
                        ans = min(ans, max(D[l][i], D[N-2-l][(i + l+1) % N]));
                    }
                }
            }

            cout << ans/2 << '.' << 5*ans%10 << '\n';
        }
    }
};
