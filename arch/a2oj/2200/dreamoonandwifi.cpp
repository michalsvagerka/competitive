#include "../../../l/lib.h"
// #include "../l/mod.h"

class dreamoonandwifi {
public:
    void solve(istream& cin, ostream& cout) {
        string S,T;
        cin >> S >> T;
        vector<int> F(11,1);
        for (int i = 1; i < 11; ++i) {
            F[i] = F[i-1]*i;
        }

        int A = count(S.begin(),S.end(),'+') - count(S.begin(),S.end(),'-');
        int B = count(T.begin(),T.end(),'+') - count(T.begin(),T.end(),'-');
        int C = count(T.begin(),T.end(),'?');
        if (abs(B-A) > C) {
            cout << "0.000000000000\n";
        } else {
            int D = (B-A+C)/2;
            cout << fixed << setprecision(12) << 1.0*F[C]/F[D]/F[C-D]/(1<<C) << endl;
        }
    }
};
