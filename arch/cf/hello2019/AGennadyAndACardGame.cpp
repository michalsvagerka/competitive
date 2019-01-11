#include "../l/lib.h"
// #include "../l/mod.h"

class AGennadyAndACardGame {
public:
void solve(istream& cin, ostream& cout) {
    string C; cin >> C;
    vector<string> H(5); cin >> H;
    for (int i = 0; i < 5; ++i) {
        if (H[i][0] == C[0] || H[i][1] == C[1]) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}
};
