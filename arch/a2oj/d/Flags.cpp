#include "../l/lib.h"
 #include "../l/mod.h"
#include "../l/matrix.h"

class Flags {
public:

    FieldMod count(int v, Matrix<FieldMod> M) {
        if (v == 0) return 0;
        auto N = M.power(v-1);
        vector<FieldMod> Z(17,1);
        Z[16] = 4;
        Z = N*Z;
        return Z[16];
    }

void solve(istream& cin, ostream& cout) {
    Matrix<FieldMod> M(17,17,0);
    for (int j = 0; j < 16; ++j) {
        bool ok = false;
        for (int i = 0; i < 16; ++i) {
            int a = i/4, b = i%4, c = j/4, d = j%4;
            if (b == c && c != d && a != b && (a&2) != (b&2) && (c&2) != (d&2) && (b || a == d)) {
                M[i][j] = 1;
                M[16][j] = 1;
            }
        }
        M[16][16] = 1;
    }

    int L, R; cin >> L >> R;
    FieldMod ans = count(R, M) - count(L-1, M) + count((R+1)/2, M) - count(L/2, M);
    cout << ans/2 << endl;

}
};
