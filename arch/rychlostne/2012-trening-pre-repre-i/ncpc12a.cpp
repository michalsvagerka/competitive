#include "../l/lib.h"
// #include "../l/mod.h"

class ncpc12a {
public:
    void solve(istream& cin, ostream& cout) {
        string s,t; cin >> s >> t;
        cout << "gn"[s.size() < t.size()] << "o\n";
    }
};
