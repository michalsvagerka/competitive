#include "../l/lib.h"
// #include "../l/mod.h"

class gridrect {
public:
    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
        pair<ll,pair<ll,ll>> Z{N-1, {1,1}};
        for (ll r = 1; r < 50000; ++r) {
            ll c = bsl(r, 2000000000ll/r+1, [&](ll q) { return r*(r+1)*q*(q+1)/4 >= N; });
            if (c==-1) continue;
            Z = min(Z, {abs(r*(r+1)*c*(c+1)/4-N), {r,c}});
            Z = min(Z, {abs(r*(r+1)*c*(c-1)/4-N), {r,c-1}});
        }
        cout << Z.y.x << ' ' << Z.y.y;
        if (Z.x == 0) {
            cout << " presne\n";
        } else {
            cout << " chyba " << Z.x << "\n";
        }
    }
};
