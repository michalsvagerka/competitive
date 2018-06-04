#include "../l/lib.h"
// #include "../l/mod.h"

class brackets {
public:
    void solve(istream& cin, ostream& cout) {
        string s; cin >> s;
        int N = s.size();
        vector<pair<ull,ull>> X(N+1,{0,0});
        X[0] = {1,1};
        ull ans = 1;
        for (char c: s) {
            if (c == '(') {
                for (int i = N-1; i >= 0; i--) {
                    X[i+1].x += X[i].x;
                    X[i+1].y += X[i].x;
                    X[i].x = 0;
                }
            } else {
                for (int i = 1; i <= N; i++) {
                    X[i-1].y += X[i].y;
                    X[i-1].x += X[i].y;
                    if (i == 1) ans += X[i].y;
                    X[i].y = 0;
                }
            }
        }
        cout << ans << endl;
    }
};
