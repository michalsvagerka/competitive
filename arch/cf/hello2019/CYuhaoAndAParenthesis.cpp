#include "../l/lib.h"
// #include "../l/mod.h"

class CYuhaoAndAParenthesis {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<string> S(N);
    cin >> S;
    vector<int> Pos(5e5+1, 0);
    vector<int> Neg(5e5+1, 0);
    
    for (string &s: S) {
        int bal = 0, lo = 0;
        for (char c: s) {
            if (c == '(') ++bal;
            else --bal;
            lo = min(lo, bal);
        }

        if (bal >= 0) {
            if (lo == 0) Pos[bal]++;
        } else if (lo == bal) Neg[-bal]++;
    }

    int ans = Pos[0]/2;
    for (int i = 1; i <= 5e5; ++i) {
        ans += min(Pos[i], Neg[i]);
    }
    cout << ans << endl;
}
};
