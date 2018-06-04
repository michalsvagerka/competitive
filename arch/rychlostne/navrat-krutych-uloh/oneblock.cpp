#include "../../../l/lib.h"
#include "../../../l/mod.h"

class oneblock {
public:
    void solve(istream& cin, ostream& cout) {
        int L, S; cin >> L >> S;
        if (L <= 2) {
            cout << "0\n";
            return;
        }

        vector2<FieldMod> Z(2,2,0);
        Z[0][0] = S*(S-1);
        Z[1][0] = S;

        for (int i = 2; i < L; ++i) {
            vector2<FieldMod> P(2,2,0);
            P[0][0] = (Z[1][0] + Z[0][0]) * (S-1);
            P[1][0] = Z[0][0];
            P[0][1] = (Z[0][1] + Z[1][1]) * (S-1);
            P[1][1] = Z[0][1] + Z[1][0];
            swap(Z,P);
        }

        cout << Z[0][1] + Z[1][1] << endl;
    }
};
