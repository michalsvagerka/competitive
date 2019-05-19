#include "../l/lib.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int P, Q; cin >> P >> Q;
            vector<int> East, West, South, North;
            set<int> X{0}, Y{0};
            for (int i = 0; i < P; ++i) {
                int x, y; char d;
                cin >> x >> y >> d;
                switch (d) {
                    case 'W':
                        West.push_back(x);
                        break;
                    case 'E':
                        East.push_back(x);
                        X.insert(x+1);
                        break;
                    case 'S':
                        South.push_back(y);
                        break;
                    case 'N':
                        North.push_back(y);
                        Y.insert(y+1);
                        break;
                }
            }

            pii bestX = {-1, 0};
            for (int x: X) {
                int cur = 0;
                for (int e: East) cur += e < x;
                for (int w: West) cur += w > x;
                bestX = max(bestX, {cur, -x});
            }

            pii bestY = {-1, 0};
            for (int y: Y) {
                int cur = 0;
                for (int n: North) cur += n < y;
                for (int s: South) cur += s > y;
                bestY = max(bestY, {cur, -y});
            }

            cout << "Case #" << t << ": ";
            cout << -bestX.y << ' ' << -bestY.y;
            cout << endl;
        }
    }
};
