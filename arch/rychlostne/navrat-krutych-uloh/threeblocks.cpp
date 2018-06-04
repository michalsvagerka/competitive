#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/matrix.h"

class threeblocks {
public:
    void solve(istream& cin, ostream& cout) {
        ll L; int S; cin >> L >> S;
        if (L <= 2) { cout << "0\n"; return; }

        Matrix<FieldMod> W(8,8,0);
        for (int i = 0; i <= 3; ++i) {
            W[i+4][i]++;
            if (i != 3) W[i+5][i+4]++;
            W[i][i+4] += S-1;
            W[i][i] += S-1;
        }

        auto V = W.power(L-2);
        vector<FieldMod> T(8, 0);
        T[0] = FieldMod{S}*FieldMod{S-1};
        T[4] = S;

        auto R = V * T;
        cout << R[3] + R[7] << endl;

    }
};
