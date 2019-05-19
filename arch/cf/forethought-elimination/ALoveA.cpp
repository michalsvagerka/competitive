#include "../l/lib.h"

class ALoveA {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int C = count(S.begin(),S.end(),'a');
        int N = S.size();
        cout << min(N, 2*C - 1) << '\n';
    }
};
