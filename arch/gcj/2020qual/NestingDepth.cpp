#include "../l/lib.h"

class NestingDepth {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string S; cin >> S;
            int N = S.size();
            string T;
            int D = 0;
            for (char s: S) {
                int d = s-'0';
                while (D > d) { T += ')'; D--; }
                while (D < d) { T += '('; D++; }
                T += s;
            }
            while (D --> 0) T += ')';
            cout << "Case #" << (t+1) << ": " << T << '\n';
        }
    }
};
