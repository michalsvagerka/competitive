#include "../../../l/lib.h"
#include "../../../l/mod.h"

class TaskD {
public:
    ll floorSqrt(ll x) {
        ll y = (ll)sqrt(x);
        while (y*y < x) ++y;
        while (y*y > x) --y;
        return y;
    }


    void solve(istream& cin, ostream& cout) {
        ll M; cin >> M;
        ll S = floorSqrt(M);

        FieldMod i2 = 1, i3 = 1, i6 = 1, i30 = 1, i42 = 1;
        i2 /= 2;
        i3 /= 3;
        i6 /= 6;
        i30 /= 30;
        i42 /= 42;
        FieldMod fm = ui(M%1000000007);

        FieldMod ans = 0;
        for (ll x = 1; x*x <= M; ++x) {
            FieldMod fx = ui(x);
            FieldMod fy = ui(floorSqrt(M-x*x));
            fx *= fx;

            FieldMod a = i3;
            FieldMod b = -fm*i2+fx-1;
            FieldMod c = -fm*fx+fm*i2+fx*fx-2*fx+2*i3;
            FieldMod d = fm*fm*fm*i6+fm*fm*i2-fm*fx*fx*i2+fm*fx*i2+fm*i3+fx*fx*fx*i3-fx*fx+2*fx*i3;

            ans += a*fy*(fy+1)*(2*fy+1)*(3*fy*fy*fy*fy+6*fy*fy*fy-3*fy+1)*i42;
            ans += b*fy*(fy+1)*(2*fy+1)*(3*fy*fy+3*fy-1)*i30;
            ans += c*fy*(fy+1)*(2*fy+1)*i6;
            ans += d*(fy+1);
        }

        cout << 4*ans + fm*(fm+1)*(fm+2)*i6 << endl;


    }
};
