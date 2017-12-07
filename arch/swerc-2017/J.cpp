#include "../../l/lib.h"
// #include "../l/mod.h"

class J {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), B(N); cin >> A >> B;
        vector<ll> AX(3), BX(3);
        for (int i = 0; i < N; ++i) {
            AX[i%3] += A[i];
            BX[i%3] += B[i];
        }

        cout << AX[0]*BX[1] + AX[1]*BX[0] + AX[2]*BX[2] << ' ' << AX[1]*BX[1] + AX[2]*BX[0] + AX[0]*BX[2] << ' '  << AX[0]*BX[0] + AX[1]*BX[2] + AX[2]*BX[1] << endl;
    }
};
