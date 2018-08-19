#include "../l/lib.h"
 #include "../l/mod.h"

class LittleElephantAndTriangle {
public:
void solve(istream& cin, ostream& cout) {
    int W, H; cin >> W >> H;
    vector2<FieldMod> C(2,2,0);
    for (int w = 0; w <= W; ++w) {
        for (int h = 0; h <= H; ++h) {
            C[w%2][h%2]++;
        }
    }

    FieldMod ans = 0;
    for (int a = 0; a < 2; ++a) {
        for (int b = 0; b < 2; ++b) {
            for (int c = 0; c < 2; ++c) {
                for (int d = 0; d < 2; ++d) {
                    for (int e = 0; e < 2; ++e) {
                        for (int f = 0; f < 2; ++f) {
                            if ((a*d + a*f + c*f + d*e + e*b + c*b)%2 == 0) {
                                FieldMod x = C[a][b], y = C[c][d], z = C[e][f];
                                y -= (a == c && b == d);
                                z -= (a == e && b == f);
                                z -= (c == e && d == f);
                                ans += x * y * z;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int dw = 2; dw <= W; ++dw) {
        for (int dh = 2; dh <= H; ++dh) {
            ans -= FieldMod{12} * (W-dw+1) * (H-dh+1) * (gcd(dw,dh)-1);
        }
    }
    for (int dw = 2; dw <= W; ++dw) {
        ans -= FieldMod{6} * (W+1-dw) * (H+1) * (dw-1);
    }

    for (int dh = 2; dh <= H; ++dh) {
        ans -= FieldMod{6} * (H+1-dh) * (W+1) * (dh-1);
    }

    cout << ans << endl;
}
};
