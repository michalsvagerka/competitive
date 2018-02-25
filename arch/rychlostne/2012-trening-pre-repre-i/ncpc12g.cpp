#include "../../../l/lib.h"
// #include "../l/mod.h"

class ncpc12g {
public:
    void solve(istream& cin, ostream& cout) {
        int K, N; cin >> K >> N;
        set<pair<pii,int>> P;
        set<pii> R;
        for (int i = 0; i < N; ++i) {
            int r,c,s,d;
            cin >> r >> c >> s >> d;
            if (r == s) {
                P.insert({pii{1,r},0});
                R.insert(pii{1, 0});
            } else {
                int dr = s - r;
                int dc = d - c;
                int g = gcd(abs(dr), abs(dc));
                dr /= g;
                dc /= g;
                if (dr < 0) {
                    dr = -dr;
                    dc = -dc;
                }

                int c0 = dr * c - r * dc;
                P.insert({pii{dc, c0}, dr});
                R.insert(pii{dc, dr});
            }
        }

        if (R.size() == 1 && P.size() + 1 >= K) { cout << "0\n"; }
        else if (R.size() > 1 && 2 * P.size() >= K) { cout << "0\n"; }
        else {
            cout << max(1, int((1 + K) / 2 - P.size())) << endl;
        }
    }
};
