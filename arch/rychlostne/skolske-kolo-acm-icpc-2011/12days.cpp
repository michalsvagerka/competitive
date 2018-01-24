#include "../l/lib.h"
// #include "../l/mod.h"

class days {
public:
    void solve(istream& cin, ostream& cout) {
        string s; cin >> s;
        int d; cin >> d;
        int q;
        if (s == "December") q = max(0, d-24);
        else q = min(d+7, 12);
        int prev = 0, tot = 0;
        for (int i = 1; i <= q; ++i) {
            prev += max(2,i);
            tot += prev;
        }
        cout << tot << endl;

    }
};
