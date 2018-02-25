#include "../../../l/lib.h"
// #include "../l/mod.h"

class concave {
public:
    void solve(istream& cin, ostream& cout) {
        map<int,int> T;
        for (int i = 1; i < 4000; ++i) {
            T[i*(i-1)/2] = i;
        }

        int R, C; cin >> R >> C;
        if (R > C) swap(R,C);
        vector<pair<pii,int>> P;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                for (int s = r+1; s < R; ++s) {
                    for (int d = 0; d < C; ++d) {
                        int dr = s-r;
                        int dc = d-c;
                        int g = gcd(dr,abs(dc));
                        dr /= g;
                        dc /= g;

                        int c0 = dr * c - r * dc;
                        P.push_back({{dc,c0},dr});
                    }
                }
            }
        }

        ll lines = 0;
        ll triangles = 0;
        ll differentSide = 0;
        ll sameSide = 0;

        sort(P.begin(),P.end());
        for (int j = 0; j < P.size(); ) {
            int h = j;
            while (j < P.size() && P[j] == P[h]) ++j;
            ll onLine = T[j-h];
            ll below = 0;
            int y = P[h].x.y;
            for (int r = 0; r < R; ++r) {
                if (y > 0) below += min(C,1+(y-1)/P[h].y);
                y += P[h].x.x;
            }
            ll above = R*C - below - onLine;
            ll triang = j-h;
            sameSide += triang * (below * (below-1) / 2+  above * (above-1) / 2);
            differentSide += triang * (below * above);
            lines += triang * (onLine-2) * (onLine-3)/12;
            triangles += triang * (onLine-2) / 3  * (below + above);
        }

        for (int r = 0; r < R; ++r) {
            ll onLine = C;
            ll triang = C*(C-1)/2;
            ll below = r*C;
            ll above = R*C-below-onLine;
            sameSide += triang * (below * (below-1) / 2 + above * (above-1) / 2);
            differentSide += triang * (below * above);
            lines += triang * (onLine-2) * (onLine-3)/12;
            triangles += triang * (onLine-2) / 3 * (below + above);
        }

        // Line: line += 1
        // Triangle: triangle+=1 sameSide+=2 differentSide+=1
        // Convex: sameSide += 4 differentSide += 2
        // Concave: sameSide += 3 differentSide += 3

        sameSide -= 2*triangles;
        differentSide -= 1*triangles;
        ll convex = (sameSide - differentSide) / 2;
        ll concave = (sameSide - 4*convex) / 3;

        cout << 3 * concave << endl;
    }
};
