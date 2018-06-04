#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class cipher {
public:
    void solve(istream& cin, ostream& cout) {
        vector2<FieldMod> D(101, 2501, 0);
        D[0][0] = 1;
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j <= 25*i; ++j) {
                for (int k = 0; k <= 25; ++k) {
                    D[i+1][j+k] += D[i][j];
                }
            }
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string S; cin >> S;
            int N = S.size(), M = 0;
            for (char c:S) M += c-'a';
            cout << D[N][M]-1 << endl;
        }

    }
};
