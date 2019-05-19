#include "../l/lib.h"
#include <numeric>

class lilypads {
public:
    vector<int> gen(int len, int beg) {
        if (len == 1) return {0};
        
        vector<int> Ans;
        vector<bool> U(len, false);
        if (beg != 0) {
            Ans.push_back(beg);
            U[beg] = true;
        }

        int l = 0, r = len-1;
        while (l < r) {
            while (l < len && U[l]) ++l;
            while (r >= 0 && U[r]) --r;
            if (l < len) { U[l] = true; Ans.push_back(l); }
            if (r > l) { U[r] = true; Ans.push_back(r); }
        }
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        int R, C; cin >> R >> C;
        int x, y; cin >> x >> y;

        vector<int> RS = gen(R, x), CS = gen(C, y);
        for (int i = 0; i < R; ++i) {
            if (i%2 == 0) {
                for (int j = 0; j < C; ++j) {
                    cout << RS[i] << ' ' << CS[j] << '\n';
                }
            } else {
                for (int j = C-1; j >= 0; --j) {
                    cout << RS[i] << ' ' << CS[j] << '\n';
                }
            }
        }
    }
};
