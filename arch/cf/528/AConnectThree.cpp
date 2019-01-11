#include "../l/lib.h"
// #include "../l/mod.h"

class AConnectThree {
public:
void solve(istream& cin, ostream& cout) {
    vector<pii> P(3);
    cin >> P;
    vector2<int> D(1001,1001,0);
    pair<int, pii> best = {1e4, {0,0}};
    for (int i = 0; i <= 1000; ++i) {
        for (int j = 0; j <= 1000; ++j) {
            for (int k = 0; k < 3; ++k) {
                D[i][j] += abs(P[k].x - i) + abs(P[k].y - j);
            }
            best = min(best, {D[i][j], {i,j}});
        }
    }

    set<pii> G;
    for (int k = 0; k < 3; ++k) {
        for (int i = min(best.y.x,P[k].x); i <= max(best.y.x,P[k].x); ++i) {
            G.insert({i,P[k].y});
        }
        for (int i = min(best.y.y,P[k].y); i <= max(best.y.y,P[k].y); ++i) {
            G.insert({best.y.x,i});
        }
    }

    cout << G.size() << '\n';
    for (pii g:G) cout << g << '\n';
}
};
