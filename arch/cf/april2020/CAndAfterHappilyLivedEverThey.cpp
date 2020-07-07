#include "../../../l/lib.h"

class CAndAfterHappilyLivedEverThey {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int A = 0;
        if (N&1) A += 16;
        if (N&2) A += 2;
        if (N&4) A += 8;
        if (N&8) A += 4;
        if (N&16) A += 1;
        if (N&32) A += 32;
        cout << A << '\n';
    }
};
