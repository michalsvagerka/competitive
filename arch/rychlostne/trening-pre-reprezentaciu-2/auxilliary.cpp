#include "../../../l/lib.h"
// #include "../l/mod.h"

class auxilliary {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        for (char s:S) {
            if (s >= '0' && s <= '9') {
                cout << '(' << s << ")+";
            } else {
                cout << "(0)+";
            }
        }
        cout << "(0)\n";
    }
};
