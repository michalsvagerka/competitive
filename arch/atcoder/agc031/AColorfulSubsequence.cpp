#include "../l/lib.h"
#include "../l/mod.h"

class AColorfulSubsequence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        vector<int> C(26, 1);
        for (char s: S) C[s-'a']++;
        FieldMod ans = 1;
        for (int i = 0; i < 26; ++i) {
            ans *= C[i];
        }
        cout << ans - 1 << '\n';
    }
};
