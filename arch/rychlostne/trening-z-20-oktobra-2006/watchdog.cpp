#include "../l/lib.h"
#include "../l/geo.h"

class watchdog {
public:
    void test(istream& cin, ostream& cout) {
        int S,H; cin >> S >> H;
        vector<Point<int>> A(H); cin >> A;
        for (int x = 1; x < S; ++x) {
            for (int y = 1; y < S; ++y) {
                int hatch = 0;
                bool ok = true;
                for (auto &a:A) {
                    if (a == Point<int>{x,y}) ok = false;
                    hatch = max(hatch, a.squaredDistance({x,y}));
                }
                int edges = min(min(x*x, y*y),min((S-x)*(S-x),(S-y)*(S-y)));
                if (hatch <= edges && ok) {
                    cout << x << ' ' << y << '\n';
                    return;
                }
            }
        }
        cout << "poodle\n";
    }

    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (ui t = 0; t < T; ++t) {
            test(cin, cout);
        }
    }
};
