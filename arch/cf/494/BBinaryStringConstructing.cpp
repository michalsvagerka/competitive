#include "../../../l/lib.h"

class BBinaryStringConstructing {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, X; cin >> A >> B >> X;
        string S;
        for (int i = 0; i < (X+1)/2; ++i) {
            S += "01";
        }
        A -= (X+1)/2;
        B -= (X+1)/2;
        X -= 2*((X+1)/2);
        X++;

        for (int i = 0; i < A-1; ++i) S = "0" + S;
        for (int i = 0; i < B-1; ++i) S += "1";
        A = min(A, 1);
        B = min(B, 1);
        if (X && A) {
            if (B) { --B; S += "1"; }
            S += "0";
            --X;
            --A;
        }

        if (X && B) {
            S = "1" + S;
            --X;
            --B;
        }
        if (A) S = "0" + S;
        if (B) S += "1";
        cout << S << endl;
    }
};
