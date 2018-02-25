#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        auto F = FieldMod::fact(3000);
        auto I = FieldMod::invfact(3000);

        int N, M; cin >> N >> M;
        vector2<FieldMod> D(N,2,0);
        for (int i = 1; i < N; ++i) D[i][0] = 1;
        D[0][1] = 1;

        FieldMod ans = FieldMod(2).pow(M-1) * I[M-1];
        for (int i = 1; i < M; ++i) {
            vector2<FieldMod> E(N,2,0);
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (j != 0) E[j-1][k||j==1] += D[j][k];
                    if (j != N-1) E[j+1][k] += D[j][k];
                }
            }
            swap(E,D);

            FieldMod cur = 0;
            for (int j = 0; j < N; ++j) {
                cur += D[j][1];
            }
            cur *= FieldMod(2).pow(M-1-i) * I[M-1-i] * I[i];
            ans += cur;
        }

        cout << 4*F[M-1]*ans << endl;
    }
};
