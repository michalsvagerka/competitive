#include "../l/lib.h"

class BAromasSearch {
public:
    void solve(istream& cin, ostream& cout) {
        ll X0, Y0, AX, AY, BX, BY;
        cin >> X0 >> Y0 >> AX >> AY >> BX >> BY;
        ll XS, YS, T; cin >> XS >> YS >> T;

        vector<pair<ll, ll>> P{{-3e16, -3e16}, {X0, Y0}};
        while (abs(P.back().x) + abs(P.back().y) <= 5e16) {
            P.push_back({AX * P.back().x + BX, AY * P.back().y + BY});
        }

        int ans = 0;
        int N = P.size();
        for (int t = 0; t < 2; ++t) {
            for (int i = 0; i < N; ++i) {
                ll dist = abs(XS-P[i].x) + abs(YS-P[i].y);
                int j = i;
                while (dist <= T) {
                    dist += abs(P[j].x-P[j+1].x) + abs(P[j].y-P[j+1].y);
                    j++;
                }
                ans = max(ans, j-i);
            }
            reverse(P.begin(),P.end());
        }

        cout << ans << endl;
//        cout << P;
    }
};
