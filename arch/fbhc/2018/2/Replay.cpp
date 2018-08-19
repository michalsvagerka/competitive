#include "../l/lib.h"
#include "../l/mod.h"

class Replay {
public:

    FieldMod brute(vector<pii> &P, vector<int> &D, int i, int S, int E) {
        if (i == D.size()) {
            for (int j = 0; j < D.size(); ++j) {
                for (int k = 0; k < D.size(); ++k) {
                    if (D[j] == 0) { // left
                        if (D[k] == 2) { // up
                            if (P[j].x > P[k].x && P[k].y < P[j].y && P[j].y < S) {
                                return 1;
                            }
                        }
                        if (D[k] == 3) { // bottom
                            if (P[j].x > P[k].x && P[k].y > P[j].y && P[j].y > S) {
                                return 1;
                            }
                        }
                    } else if (D[j] == 1) { // right
                        if (D[k] == 2) { // up
                            if (P[j].x < P[k].x && P[k].y < P[j].y && P[j].y < E) {
                                return 1;
                            }
                        } else if (D[k] == 3) { // bottom
                            if (P[j].x < P[k].x && P[k].y > P[j].y && P[j].y > E) {
                                return 1;
                            }
                        }
                    }
                }
            }
            return 0;
        } else {
            FieldMod ans = 0;
            for (int j = 0; j < 4; ++j) {
                D[i] = j;
                ans += brute(P, D, i + 1, S, E);
            }
            return ans;
        }
    }

    FieldMod smart(const vector<pii> &P, int N, int S, int E) {
        map<pair<pii,pii>, FieldMod> G;
        G[{{2e9, -2e9},{-2e9, 2e9}}] = 1;
        for (int i = 0; i < N; ++i) {
            map<pair<pii,pii>, FieldMod> W;
            for (auto &g:G) {
                int lo = g.x.x.x;
                int hi = g.x.x.y;
                int loR = g.x.y.x;
                int hiR = g.x.y.y;
                FieldMod c = g.y;
                if (P[i].y < hi && P[i].y > S) {
                } else if (P[i].y > lo && P[i].y < S) {
                } else {
                    // can do left
                    W[g.x] += c;
                }

                // go up
                if (loR < P[i].y) {
                    W[{{min(lo, P[i].y), hi}, g.x.y}] += c;
                }


                // go down
                if (hiR > P[i].y) {
                    W[{{lo, max(hi, P[i].y)}, g.x.y}] += c;
                }

                // go right
                if (P[i].y < E) loR = max(loR, P[i].y);
                if (P[i].y > E) hiR = min(hiR, P[i].y);
                W[{g.x.x, {loR, hiR}}] += c;
            }

            swap(W, G);
        }

        FieldMod ans = 0;
        for (auto &g:G) ans += g.y;

        return FieldMod{4}.pow(N) - ans;
    }

void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, S, E; cin >> N >> S >> E;
        vector<pii> P(N); cin >> P;
        sort(P.begin(),P.end());


//        vector<int> D(N);
//        cout << brute(P, D, 0, S, E) << '\n';

        FieldMod ans = smart(P, N, S, E);
        cout << "Case #" << t+1 << ": " << ans << '\n';
    }

}
};
