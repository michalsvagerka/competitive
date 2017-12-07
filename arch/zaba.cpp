#include "../l/lib.h"
// #include "../l/mod.h"

class zaba {
public:
    vector<int> gen(int l) {
        if (l == 1) return {1};
        vector<int> sol{2,1};
        for (int k = 3; k <= l; k+=4) {
            if (k+1 <= l) sol.push_back(k+1);
            sol.push_back(k);
            if (k+3 <= l) sol.push_back(k+3);
            if (k+2 <= l) sol.push_back(k+2);
        }
        return sol;
    }

    void solve(istream& cin, ostream& cout) {
        int R, C; cin >> R >> C;
        auto rows = gen(R);
        auto cols = gen(C);
        for (int c = 0; c < C; ++c) {
            for (int r = 0; r < R; ++r) {
                cout << rows[c%2 ? r : R-1-r] << ' ' << cols[c] << '\n';
            }
        }
    }
};
