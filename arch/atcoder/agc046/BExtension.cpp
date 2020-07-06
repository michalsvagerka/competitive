#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class BExtension {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, C, D; cin >> A >> B >> C >> D;
        vector2<FF> E(C+1, D+1, 0);
        E[A][B] = 1;
        for (int a = A; a < C; ++a) {
            FF Z = 0;
            for (int b = B; b <= D; ++b) {
                Z *= a;
                Z += E[a][b];
                E[a+1][b] += E[a][b] * b;
                E[a+1][b] += Z - E[a][b];
            }
        }

        for (int b = B; b < D; ++b) {
            E[C][D] += E[C][b] * FF{C}.pow(D-b);
        }

        cout << E[C][D] << '\n';
    }
};
