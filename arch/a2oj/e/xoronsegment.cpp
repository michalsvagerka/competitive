#include "../../../l/lib.h"
 #include "../../../l/segtree.h"

constexpr int B = 20;

class xoronsegment {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<XorTree<int>> T(B);
        vector<int> W(N);
        for (int i = 0; i < B; ++i) {
            for (int j = 0; j < N; ++j) {
                W[j] = !!(A[j] & (1 << i));
            }
            T[i].setup(W);
        }

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int t, l, r; cin >> t >> l >> r;
            --l; --r;
            if (t == 1) {
                ll ans = 0;
                for (int i = 0; i < B; ++i) {
                    ans += ll(T[i].get(l,r))<<i;
                }
                cout << ans << '\n';
            } else {
                int x; cin >> x;
                for (int i = 0; i < B; ++i) {
                    if (x&(1<<i)) {
                        T[i].put(l,r,true);
                    }
                }
            }
        }
    }
};
