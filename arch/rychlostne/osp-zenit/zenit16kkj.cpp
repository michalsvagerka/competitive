#include "../l/lib.h"
#include "../l/nsegtree.h"

class zenit16kkj {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<ll> A(N); cin >> A;
        LAddMaxTree<ll> T(A, 0LL, 0LL);
        for (int q = 0; q < Q; ++q) {
            int t,a,b,c; cin >> t >> a >> b >> c;
            if (t == 0) {
                cout << T.get(a-1, b-1) << '\n';
            } else {
                T.put(a-1,b-1,c);
            }
        }
    }
};
