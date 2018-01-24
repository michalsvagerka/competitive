#include "../l/lib.h"
// #include "../l/mod.h"

class ufstrike {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int L,W,B; cin >> L >> W >> B;
            int xs, ys, xf, yf; cin >> xs >> ys >> xf >> yf;
            ll dist = 1e18;
            set<vector<int>> R;
            for (int i = -B; i <= B; ++i) {
                int x = L*i + ((i%2==0)?xf:(L-xf));
                for (int j : {B-abs(i),abs(i)-B}) {
                    int y = W*j + ((j%2==0)?yf:(W-yf));
                    ll dx = x-xs, dy = y-ys;
                    ll curDist = dx*dx+dy*dy;
                    if (curDist < dist) {
                        dist = curDist;
                        R.clear();
                    }
                    if (curDist == dist) {
                        vector<int> Z(4,0);
                        Z[0] = j>0 ? j/2 + j%2 : -j/2;
                        Z[1] = i>0 ? i/2 + i%2 : -i/2;
                        Z[2] = j>0 ? j/2 : -j/2 -j%2;
                        Z[3] = i>0 ? i/2 : -i/2 -i%2;
                        R.insert(Z);
                    }
                }
            }
            for (auto r:R) cout << r;
            cout << "0\n";
        }
    }
};
