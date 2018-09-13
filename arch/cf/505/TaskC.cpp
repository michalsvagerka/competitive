#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int N = S.size();
    S += S;
    int ans = 1, cur = 1;
    for (int i = 1; i < 2*N; ++i) {
        if (S[i] != S[i-1]) { ans = max(ans, ++cur); }
        else cur = 1;
    }
    cout << min(ans, N) << endl;
}
};
