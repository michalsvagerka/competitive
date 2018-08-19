#include "../l/lib.h"
// #include "../l/mod.h"

class LeftToRightGame {
public:
    int L,M;
    vector3<bool> K, D;

    bool wins(int rem, int len, int p) {
        if (len == 0) {
            if (p) return rem != 0;
            else return rem == 0;
        }
        if (K[len][rem][p]) return D[len][rem][p];
        K[len][rem][p] = true;
        D[len][rem][p] = false;
        for (int i = 0; i < 10; ++i) {
            if (i == 0 && len == L) continue;
            if (!wins((10 * rem + i)%M, len-1, 1-p)) D[len][rem][p] = true;
        }

        return D[len][rem][p];
    }


    string whoWins(int length, int divisor) {
        L = length;
        M = divisor;
        D = K = vector3<bool>(L+1, M, 2, false);
        if (wins(0, L, 1)) {
            return "Alice";
        } else {
            return "Bob";
        }


    }

void solve(istream& cin, ostream& cout) {
    int length, divisor;
    cin >> length >> divisor;
    cout << whoWins(length, divisor) << endl;
}
};
