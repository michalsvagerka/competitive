#include "../../../l/lib.h"
// #include "../l/mod.h"

class ncpc12d {
public:
    void solve(istream& cin, ostream& cout) {
        int X;
        string S;
        cin >> X >> S;
        int D = 0, N = S.size();
        for (int i = 0; i < N; ++i) {
            int cur = (S[i] == 'W') - (S[i] == 'M');
            if (abs(D+cur) <= X) D += cur;
            else if (i != N-1 && S[i+1] != S[i]) ++i;
            else {
                cout << i << endl;
                return;
            }
        }
        cout << N << endl;
    }
};
