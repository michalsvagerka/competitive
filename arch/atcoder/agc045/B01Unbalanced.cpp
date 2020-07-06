#include "../l/lib.h"

class B01Unbalanced {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        cout << bsl(1, N, [&](int bal) {
            int lo = 0, hi = bal;
            bool fixedParity = false;
            int parity = 0;
            for (int i = N - 1; i >= 0; --i) {
                parity = 1-parity;
                if (S[i] == '0') {
                    lo++;
                    hi++;
                } else if (S[i] == '1') {
                    hi--;
                    lo--;
                } else {
                    lo--;
                    hi++;
                }

                lo = max(lo, 0);
                hi = min(hi, bal);
                if (lo == hi && fixedParity && lo % 2 != parity % 2) {
                    return false;
                }

                if (lo == hi) {
                    fixedParity = true;
                    parity = lo%2;
                }
                if (lo > hi) return false;
            }
            return true;
        });
//            int lo = 0, hi = 0;
//            for (int i = 0; i < N; ++i) {
//                if (S[i] == '0') {
//                    lo++; hi++;
//                } else if (S[i] == '1') {
//                    lo--; hi--;
//                } else {
//                    lo--; hi++;
//                }
//
//                lo = max(lo, -bal);
//                hi = min(hi, bal);
//            }
    }
};
