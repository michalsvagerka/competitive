#include "../l/lib.h"

class APBinary {
public:
    void solve(istream& cin, ostream& cout) {
        int N, P; cin >> N >> P;
        int i = 1;
        while (true) {
            int S = N - i*P;
            if (S <= 0) {
                cout << "-1\n";
                return;
            }

            int lo = __builtin_popcount(S);
            int hi = S;
            
            if (lo <= i && i <= hi) {
                cout << i << endl;
                return;
            }

            i++;
        }
    }
};
