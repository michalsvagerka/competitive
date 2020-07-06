#include "../l/lib.h"
#include "../l/geo.h"

typedef long double ld;

class covidtunnel {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int R = 6371047;
        for (int i = 0; i < N; ++i) {
            ld a,b,c,d;
            cin >> a >> b >> c >> d;
            a *= PI/180;
            b *= PI/180;
            c *= PI/180;
            d *= PI/180;

            ld phi1 = a;
            ld phi2 = c;
            ld deltaphi = c-a;
            ld deltalambda = d-b;
            ld aa = sin(deltaphi/2) * sin(deltaphi/2) + cos(phi1) * cos(phi2) * sin(deltalambda/2) * sin(deltalambda/2);
            ld cc = 2 * atan2(sqrt(aa), sqrt(1-aa));
            ld greatCircle = R * cc;

            ld x = cos(a) * cos(b) - cos(c) * cos(d);
            ld y = cos(a) * sin(b) - cos(c) * sin(d);
            ld z = sin(a) - sin(c);
            ld direct = R * sqrt(x*x+y*y+z*z);

            cout << fixed << setprecision(10) << greatCircle - direct << '\n';
        }

    }
};
