#include "../l/lib.h"
#include "../l/segtree.h"
#include "../l/random.h"


class t2osvetlenie {
public:
    void solve(istream& cin, ostream& cout) {
        XorTree<int> R,C;
        int r,c,q; cin >> r >> c >> q;
        R.setup(r, 0);
        C.setup(c, 0);
        while (q--) {
            int t,a,b,x,y; cin >> t >> a >> b;
            switch (t) {
                case 1:
                    C.put(a,b,1);
                    break;
                case 2:
                    R.put(a,b,1);
                    break;
                case 3:
                    cin >> x >> y;
                    ll e = C.get(a,x), f = R.get(b,y);
                    cout << e*(y-b-f+1) + (x-a-e+1)*f << '\n';
                    break;
            }
        }
    }
};
