#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/matrix.h"

class stairsandlines {
public:
    vector<vector<vector<FieldMod>>> Z;

    void solve(istream& cin, ostream& cout) {
        vector<FieldMod> C{1};
        for (int i = 1; i <= 7; ++i) {
            vector<FieldMod> D(1<<i, 0);
            for (int j = 0; j < (1<<(i-1)); ++j) {
                D[j|(1<<(i-1))] = C[j];
            }

            int w; cin >> w;
            Matrix<FieldMod> T(1<<i,1<<i);
            for (int j = 0; j < (1 << i); ++j) {
                for (int k = 0; k < (1 << i); ++k) {
                    for (int l = 0; l < (1<<(i-1)); ++l) {
                        int g = 1|(l<<1)|(1<<i);
                        if ((j&k&g&(g>>1)) == 0) {
                            T[j][k]++;
                        }
                    }
                }
            }
            C = T.power(w) * D;
        }

        cout << C.back() << endl;

    }
};
