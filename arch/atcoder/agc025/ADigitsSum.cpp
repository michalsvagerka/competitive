#include "../l/lib.h"
// #include "../l/mod.h"

class ADigitsSum {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int ans = 10000000;
        for (int i = 1; i < N; ++i) {
            stringstream a, b;
            a << i;
            b << N-i;
            int cur = 0;
            for (char s: a.str()) cur += s-'0';
            for (char s: b.str()) cur += s-'0';
            ans = min(ans, cur);
        }
        cout << ans << endl;
    }
};
