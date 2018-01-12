#include "../l/lib.h"
#include "../l/geo.h"

class most {
public:
    double ans = 20000;

    void check(const pii&a,const pii&b, const pii&c) {
        ans = min(ans, pointSegmentDistance(a,b,c));
    }

    void read(istream& cin, vector<pii> &Z) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            int x,y; cin >> x >> y;
            Z.push_back({x,y});
        }
    }



    void solve(istream& cin, ostream& cout) {
        vector<pii> L,R;
        read(cin, L);
        read(cin, R);

        for (int i = 0; i < 2; ++i) {
            for (auto l:L) {
                check(l, {R[0].x, -20000}, R[0]);
                check(l, {R.back().x, 20000}, R.back());
                for (int j = 0; j < R.size()-1; ++j) {
                    check(l, R[j], R[j+1]);
                }
            }

            swap(L,R);
        }

        cout << fixed << setprecision(17) << ans << endl;
    }
};
