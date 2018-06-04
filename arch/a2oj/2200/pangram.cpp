#include "../../../l/lib.h"
// #include "../l/mod.h"

class pangram {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        vector<bool> V(26, false);
        for (char s:S) {
            if (s>='a' && s<='z') V[s-'a'] = true;
            else V[s-'A'] = true;
        }

        if (count(V.begin(),V.end(),false) == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
