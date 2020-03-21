#include "../l/lib.h"
#include "../l/nsegtree.h"

class EAlyonaAndTowers {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        LAddMaxTree<ll> T(A, 0, 0);

        vector<int> L(N, 0), R(N, N-1), D(N);
        for (int i = N-2; i >= 0; --i) if (A[i] > A[i+1]) R[i] = R[i+1]; else R[i] = i;
        for (int i = 1; i < N; ++i) if (A[i] > A[i-1]) L[i] = L[i-1]; else L[i] = i;
        for (int i = 0; i < N; ++i) D[i] = R[i] - L[i];
        LAddMaxTree<int> LL(L, 0, 0);
        LAddMinTree<int> RR(R, 1000000, 0);
        LAddMaxTree<int> DD(D, 0, 0);

        auto setLeft = [&](int l, int target) {
            int orig = LL.get(l);
            int end = LL.longestPrefix(l, [&](int x) { return x == orig; });
            LL.put(l, end, target - orig);
            DD.put(l, end, -(target - orig));
        };
        auto setRight = [&](int r, int target) {
            int orig = RR.get(r);
            int begin = RR.longestSuffix(r, [&](int x) { return x == orig; });
            RR.put(begin, r, target - orig);
            DD.put(begin, r, target - orig);
        };

        int M; cin >> M;
        for (int i = 0; i < M; ++i) {
            int l, r, d; cin >> l >> r >> d;
            --l; --r;
            if (l > 0) {
                ll a = T.get(l-1);
                ll b = T.get(l);

                if (a >= b && a <= b + d) {
                    if (a < b + d) setLeft(l, LL.get(l-1));
                    if (a > b) setRight(l-1, l-1);
                }
            }

            if (r < N-1) {
                ll a = T.get(r+1);
                ll b = T.get(r);

                if (a >= b && a <= b + d) {
                    if (a < b + d) setRight(r, RR.get(r+1));
                    if (a > b) setLeft(r+1, r+1);
                }
            }

            T.put(l, r, d);
            cout << DD.get(0, N-1) + 1 << '\n';
        }
    }
};
