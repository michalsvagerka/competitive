#include "../../../l/lib.h"
// #include "../l/mod.h"

class dvauseky {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int cnt = count(S.begin(),S.end(),'1');
        int N = S.size();
        if (N == cnt || N == 0) {
            cout << 1 << ' ' << N-1 << ' ' << 2 << ' ' << N << endl;
            return;
        }

        int lo1 = N, lo0 = N, hi1 = 0, hi0 = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '0') {
                hi0 = i;
                lo0 = min(lo0, i);
            } else {
                hi1 = i;
                lo1 = min(lo1, i);
            }
        }

        if (hi0 - lo0 > hi1 - lo1) {
            cout << lo0+1 << ' ' << hi0 << ' ' << lo0 + 2 << ' ' << hi0+1 << endl;
        } else {
            cout << lo1+1 << ' ' << hi1 << ' ' << lo1 + 2 << ' ' << hi1+1 << endl;
        }

    }
};
