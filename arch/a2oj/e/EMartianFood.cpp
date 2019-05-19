#include "../l/lib.h"
#include "../l/geo.h"

class EMartianFood {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int R, r, k;
            cin >> R >> r >> k;
            Circle<double> Hond({double(R),0}, R*R);
            Circle<double> Terr({double(r),0}, r*r);
            Circle<double> Inv({0,0}, r*r);
            double x1 = Inv.intersections(Hond).x.x;
            double x2 = Inv.intersections(Terr).x.x;
            
            double smallDiam = x2-x1;
            double smallY = k * smallDiam;
            
            Point<double> A(Inv.invert({x1, smallY})),
                          B(Inv.invert({x2, smallY})),
                          C(Inv.invert({(x1+x2)/2, smallY + smallDiam/2}));
            
            
            Circle<double> Ans(A, B, C);
            cout << fixed << setprecision(10) << sqrt(Ans.sqRadius) << endl;
        }
    }
};
