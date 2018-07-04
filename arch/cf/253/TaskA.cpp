#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<string> S(N); cin >> S;
    set<string> D;
    for (string &s:S) D.insert(s);

    string F = "12345BYWGR";

    int ans = 10;
    for (int i = 0; i < (1<<10); ++i) {
        set<int> C;
        for (const string&s:D) {
            int f = 0;
            for (int j = 0; j < 10; ++j) {
                if (i & (1<<j)) {
                    if (s[0] == F[j] || s[1] == F[j]) f |= 1<<j;
                }
            }
            C.insert(f);
        }
        if (C.size() == D.size()) {
            ans = min(ans, __builtin_popcount(i));
        }

    }
    cout << ans << '\n';
}
};
