#include "../l/lib.h"

class FNeatWords {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        cin >> S;
        string T = "WETYIAFHKLZXVNM";
        bool a = false, b = false;
        for (char s:S) {
            bool ok = false;
            for (char t:T) {
                ok |= t==s;
            }
            if (ok) a = true;
            else b = true;
        }
        
        if (a!=b) cout << "YES\n"; else cout << "NO\n";
    }
};
