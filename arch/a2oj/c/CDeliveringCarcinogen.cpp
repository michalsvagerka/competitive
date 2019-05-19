#include "../l/lib.h"
#include "../l/geo.h"

class CDeliveringCarcinogen {
public:
    void solve(istream& cin, ostream& cout) {
        double XP, YP, VP;
        cin >> XP >> YP >> VP;

        double X, Y, V, R;
        cin >> X >> Y >> V >> R;
        Point<double> Orig{X, Y};
        Point<double> Zero{0, 0};
        Circle<double> Forbidden{Zero, R*R};

        double RR = sqrt(XP*XP + YP*YP);
        double init = atan2(YP, XP);
        cout << fixed << setprecision(10) << bsld(0.0, 1e5, [&](double t) {
            double angle = (t * VP) / RR;
            Point<double> New{RR * cos(angle + init), RR * sin(angle + init)};
            Segment<double> straight(New, Orig);

            double dist = straight.distance(Zero);
            if (dist >= R) {
                return straight.length() <= t * V;
            } else {
                auto solve = [&](Point<double> a, Point<double> b) {
                    double ang1 = atan2(a.y, a.x);
                    double ang2 = atan2(b.y, b.x);
                    if (ang2 < ang1) ang2 += 2*PI;
                    double ang = ang2 - ang1;
                    if (ang > PI) ang = 2*PI - ang;
                    return Orig.distance(a) + New.distance(b) + ang * R;
                };

                Circle<double> Thales1{Orig, Zero};
                Circle<double> Thales2{New, Zero};

                auto Inter1 = Thales1.intersections(Forbidden);
                auto Inter2 = Thales2.intersections(Forbidden);

                double dist = min(solve(Inter1.x, Inter2.x), solve(Inter1.x, Inter2.y));
                dist = min(dist, min(solve(Inter1.y, Inter2.x), solve(Inter1.y, Inter2.y)));
                return dist <= t * V;
            }
        }, 1e-9) << endl;
    }
};
