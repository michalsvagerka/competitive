#include "../l/lib.h"
 #include "../l/mod.h"

class A {
public:
void solve(istream& cin, ostream& cout) {
    string S;
    cin >> S;
    int N = S.size();
    int M = 1 << 10;
    vector2<FieldMod> D(M, 11, 0);
    D[0][10] = 1;
    for (int i = 0; i < N; ++i) {
        int d = S[i] - '0';
        for (int m = M - 1; m >= 0; --m) {
            if (!(m & (1 << d))) {
                D[m | (1 << d)][10] += D[m][10];
            }

            FieldMod g = D[m][d];
            D[m][d] += D[m][10];
            D[m][10] = g;
        }
    }

    FieldMod ans = 0;
    for (int m = M - 1; m > 0; --m) {
        ans += D[m][10];
    }

    cout << ans << endl;
}
};
