#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class jzzhuandnumbers {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector2<int> S(21, 1<<20, 0);
        for (int &a:A) S[0][a]++;

        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < (1<<20); ++j) {
                S[i+1][j] = S[i][j];
                if (!(j&(1<<i))) S[i+1][j] += S[i][j | (1<<i)];
            }
        }

        FieldMod ans = 0;
        for (int i = 0; i < (1<<20); ++i) {
            if (__builtin_popcount(i)%2 == 0) {
                ans += FieldMod{2}.pow(S[20][i]);
            } else {
                ans -= FieldMod{2}.pow(S[20][i]);
            }
        }
        cout << ans << '\n';
    }
};
