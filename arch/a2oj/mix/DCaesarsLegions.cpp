#include "../l/lib.h"
 #include "../l/mod.h"

 typedef Field<100000000> W;

class DCaesarsLegions {
public:
void solve(istream& cin, ostream& cout) {
    int N1, N2, K1, K2; cin >> N1 >> N2 >> K1 >> K2;
    vector3<W> D(N1+1,K1+1,K2+1,0);
    D[N1][0][0] = 1;
    for (int i = 0; i < N1+N2; ++i) {
        vector3<W> E(N1+1,K1+1,K2+1,0);
        for (int n1 = 0; n1 <= N1; ++n1) {
            int n2 = N1 + N2 - i - n1;
            if (n2 < 0) break;
            for (int k1 = 0; k1 <= K1; ++k1) {
                for (int k2 = 0; k2 <= K2; ++k2) {
                    if (D[n1][k1][k2] == 0) continue;
                    if (n1 && k1 != K1) E[n1-1][k1+1][0] += D[n1][k1][k2];
                    if (n2 && k2 != K2) E[n1][0][k2+1] += D[n1][k1][k2];
                }
            }
        }
        swap(D,E);
    }

    W ans = 0;
    for (int k1 = 0; k1 <= K1; ++k1) {
        for (int k2 = 0; k2 <= K2; ++k2) {
            ans += D[0][k1][k2];
        }
    }
    cout << ans << '\n';
}
};
