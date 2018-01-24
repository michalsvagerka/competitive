#include "../l/lib.h"
// #include "../l/mod.h"

class hvezdar {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int x0,y0,x1,y1,x2,y2;
            cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
            bool detour = false;
            detour |= y0 == y2 && in(min(x0,x1),x2,max(x0,x1)+1);
            detour |= x1 == x2 && in(min(y0,y1),y2,max(y0,y1)+1);
            cout << 2+2*detour << '\n';
            if (detour) cout << "UD"[y1>=y0] << " 1\n";
            cout << "LR"[x1>=x0] << ' ' << abs(x1-x0)+detour << '\n';
            cout << "DU"[y1>=y0] << ' ' << abs(y1-y0)+detour << '\n';
            if (detour) cout << "RL"[x1>=x0] << " 1\n";
        }
    }
};
