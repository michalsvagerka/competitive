#include "../../../l/lib.h"
#include "../../../l/mod.h"

class gregandfriends {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        K /= 50;
        int a = 0, b = 0;
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            if (x == 50) ++a; else ++b;
        }

        auto F = FieldMod::fact(51);
        auto I = FieldMod::invfact(51);

        vector3<FieldMod> S(400, a+1, b+1, 0);
        vector3<bool> P(400, a+1, b+1, false);
        S[0][a][b] = 1;
        P[0][a][b] = true;

        for (int i = 1; i < 400; ++i) {
            for (int j = 0; j <= a; ++j) {
                for (int k = 0; k <= b; ++k) {
                    if (!P[i-1][j][k]) continue;
                    bool pos = (i%2==1);
                    int o1 = pos?j:a-j;
                    int o2 = pos?k:b-k;
                    for (int l = 0; l <= o1; ++l) {
                        for (int m = 0; m <= o2; ++m) {
                            if (l == 0 && m == 0) continue;
                            if (l+2*m > K) break;
                            S[i][j+(pos?-l:l)][k+(pos?-m:m)] += S[i-1][j][k] * F[o1] * I[l] * I[o1-l] * F[o2] * I[m] * I[o2-m];
                            P[i][j+(pos?-l:l)][k+(pos?-m:m)] = true;
                        }
                    }
                }
            }

            if (P[i][0][0]) {
                cout << i << '\n' << S[i][0][0] << '\n';
                return;
            }
        }


        cout << "-1\n0\n";
    }
};
