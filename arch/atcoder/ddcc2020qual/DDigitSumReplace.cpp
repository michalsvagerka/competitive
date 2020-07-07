#include "../../../l/lib.h"

class DDigitSumReplace {
public:
    void solve(istream& cin, ostream& cout) {
        int M; cin >> M;
        ll tot = 0;
        ll dig = 0;
        for (int i = 0; i < M; ++i) {
            int d; ll c;
            cin >> d >> c;
            dig += c;
            tot += d*c;
        }

        cout << dig + (tot-1)/9 - 1 << '\n';
    }
};
