#include "../../../l/lib.h"

class BDeleteFromTheLeft {
public:
    void solve(istream& cin, ostream& cout) {
        string S, T; cin >> S >> T;
        reverse(S.begin(),S.end());
        reverse(T.begin(),T.end());
        int i = 0;
        while (i < S.size() && i < T.size() && S[i] == T[i]) ++i;
        cout << S.size() + T.size() - 2*i << '\n';
    }
};
