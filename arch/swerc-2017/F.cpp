#include "../../l/lib.h"
// #include "../l/mod.h"

class F {
public:
    void solve(istream& cin, ostream& cout) {
        ll S = 0;
        ll W; cin >> W;
        int N; cin >> N;

        for (int i = 0; i < N; ++i) {
            int w,l; cin >> w >> l;
            S += (ll)w*l;
        }
        cout << S / W << endl;
    }
};
