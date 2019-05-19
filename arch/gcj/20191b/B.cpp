#include "../l/lib.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {


        int T, W; cin >> T >> W;
        for (int t = 1; t <= T; ++t) {
            cout << "56" << endl;
            ll x; cin >> x;
            if (x == -1) return;
            vector<int> Ans(6);

            cout << "224" << endl;
            ll y; cin >> y;
            if (y == -1) return;
            Ans[5] = (y>>37)&127;
            Ans[4] = (y>>44)&127;
            Ans[3] = (y>>56)&127;

            x -= Ans[3]<<14;
            x -= Ans[4]<<11;
            x -= Ans[5]<<9;
            Ans[0] = (x>>56)&127;
            Ans[1] = (x>>28)&127;
            Ans[2] = (x>>18)&127;

            cout << Ans;
            flush(cout);
            int res; cin >> res;
            if (res == -1) return;
        }
    }
};
