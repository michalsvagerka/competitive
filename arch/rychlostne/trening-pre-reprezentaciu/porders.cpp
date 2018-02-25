#include "../../../l/lib.h"

class porders {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> P(N); cin >> P;
        set<pii> Z;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                int dx = P[i].x - P[j].x;
                int dy = P[i].y - P[j].y;
                if (dx == 0) {
                    Z.insert({0,1});
                } else {
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                    int g = gcd(abs(dx), abs(dy));
                    Z.insert({dx / g, dy / g});
                }
            }
        }
        cout << Z.size() << endl;
    }
};
