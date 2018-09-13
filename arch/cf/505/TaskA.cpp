#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    string S; cin >> S;
    vector<int> C(26, 0);
    for (char s:S) C[s-'a']++;
    for (int i = 0; i < 26; ++i) {
        if (C[i] >= 2) {
            cout << "Yes\n";
            return;
        }
    }

    if (N == 1) { cout << "Yes\n"; }
    else cout << "No\n";
}
};
