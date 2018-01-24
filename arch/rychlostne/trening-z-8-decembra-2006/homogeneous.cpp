#include "../l/lib.h"
// #include "../l/mod.h"

class homogeneous {
public:
    void solve(istream& cin, ostream& cout) {
        ui n; cin >> n;
        while (n) {
            vector2<int> A(n,n); cin >> A;
            bool hom = true;
            for (ui i = 0; i < n; ++i) {
                for (ui j = 0; j < n; ++j) {
                    hom &= (A[0][0]+A[i][j]==A[i][0]+A[0][j]);
                }
            }
            if (!hom) cout << "not ";
            cout << "homogeneous\n";

            cin >> n;
        }
    }
};
