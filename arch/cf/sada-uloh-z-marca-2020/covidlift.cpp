#include "../l/lib.h"

class covidlift {
public:
    void solve(istream& cin, ostream& cout) {
        int N, P; cin >> N >> P;
        set<int> LO, HI;
        for (int i = 0; i < N; ++i) {
            int c; cin >> c;
            if (c < P) LO.insert(c); else HI.insert(c);
        }

        int down = LO.empty() ? 0 : P - *LO.begin();
        int up = HI.empty() ? 0 : *HI.rbegin() - P;
        if (down <= up) {
            for (auto it = LO.rbegin(); it != LO.rend(); ++it) {
                cout << *it << '\n';
            }
        }

        for (auto it = HI.begin(); it != HI.end(); ++it) {
            cout << *it << '\n';
        }
        if (down > up) {
            for (auto it = LO.rbegin(); it != LO.rend(); ++it) {
                cout << *it << '\n';
            }
        }

    }
};
