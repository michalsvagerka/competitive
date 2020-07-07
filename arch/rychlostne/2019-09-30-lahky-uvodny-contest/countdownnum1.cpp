#include "../../../l/lib.h"
#include <sstream>

class countdownnum1 {
public:
    vector<int> X;
    int T;

    vector<map<ll, string>> C;



    void solve(istream& cin, ostream& cout) {
        X.resize(6); cin >> X;
        cin >> T;
        C.resize(1<<6);
        for (int i = 0; i < 6; ++i) {
            C[1<<i][X[i]] = to_string(X[i]);
        }

        for (int j = 0; j < (1<<6); ++j) {
            if (__builtin_popcount(j) <= 1) continue;
            for (int k = 1; k < j; ++k) {
                if ((j&k) == k) {
                    int l = j^k;
                    for (auto &c: C[k]) {
                        for (auto &d: C[l]) {
                            C[j][c.x + d.x] = c.y + " " + d.y + " +";
                            C[j][c.x - d.x] = c.y + " " + d.y + " -";
                            C[j][c.x * d.x] = c.y + " " + d.y + " *";
                            if (d.x != 0 && c.x % d.x == 0) C[j][c.x / d.x] = c.y + " " + d.y + " /";
                        }
                    }
                }
            }
        }
        
        
        pair<pair<ll,ll>, string> Best = {{100000, 0}, ""};
        for (int i = 1; i < (1<<6); ++i) {
            for (auto &c: C[i]) {
                Best = min(Best, {{abs(c.x - T), c.x}, c.y});
            }
        }
        cout << Best.x.y << '\n' << Best.y << '\n';
    }
};
