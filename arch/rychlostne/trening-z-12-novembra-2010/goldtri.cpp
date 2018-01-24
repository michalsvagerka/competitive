#include "../l/lib.h"
#include "../l/geo.h"

class goldtri {
public:
    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
        vector<Point<ll>> P(N);
        for (ui i = 0; i < N; ++i) {
            cin >> P[i].x >> P[i].y;
        }
        sort(P.begin(),P.end(),[](Point<ll>&a,Point<ll>&b) {
            if (a.y==0&&a.x>0) return true;
            if (b.y==0&&b.x>0) return false;
            if (a.y>0&&b.y<0) return true;
            return !(a.y<0&&b.y>0) && (a.x*b.y-a.y*b.x)>1e-6;
        });
        Point<ll> O(0,0);
        ui e = 1;
        ll g = N*(N-1)*(N-2)/6;
        for (ui b = 0; b < N; ++b) {
            while (b != e && orientation(P[b], O, P[e]) == -1) {
                e = (e+1)%N;
            }
            ll c = (N+e-b-1)%N;
            g -= c*(c-1)/2;
        }
        cout << g << endl;
    }
};
