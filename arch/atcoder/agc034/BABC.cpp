#include "../l/lib.h"

class BABC {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int cur = 0;
        ll ans = 0;
        int N = S.size();
        reverse(S.begin(),S.end());
        for (int i = 0; i < N; ++i) {
            if (cur % 2 == 0) {
                 if (S[i] == 'C') {
                     cur++;
                 } else if (S[i] == 'A') {
                     ans += cur/2;
                 } else {
                     cur = 0;
                 }
            } else {
                if (S[i] == 'B') {
                    ++cur;
                } else if (S[i] == 'C') {
                    cur = 1;
                } else {
                    cur = 0;
                }
            }
        }
        cout << ans << endl;
    }
};
