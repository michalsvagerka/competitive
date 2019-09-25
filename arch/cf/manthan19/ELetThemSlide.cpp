#include "../l/lib.h"
#include "../l/nsegtree.h"
#include "../l/consttree.h"

class ELetThemSlide {
public:
    void solve(istream& cin, ostream& cout) {
        int N, W; cin >> N >> W;
        AddSumTree<ll> T(W, 0, 0);
        for (int i = 0; i < N; ++i) {
            int M; cin >> M;
            vector<ll> A(M);
            cin >> A;

            ConstTree<ll, MaxQOp<ll>> CT(A);
            for (int j = 0; j < M; ++j) {
                int l = M - W + j;
                int r = j;
                ll me = -1e9;
                if (l < 0) me = 0;
                me = max(me, CT.get(max(0, l), r));
                T.put(j, me);
            }

            if (M < W-M) {
                ll q = max(0LL, CT.get(0, M-1));
                T.put(M, W-M-1, q);
            }

            for (int j = max(M, W-M); j < W; ++j) {
                int l = j-W+M;
                int r = M-1;
                ll me = max(0LL, CT.get(l, r));
                T.put(j, me);
            }
        }

        for (int i = 0; i < W; ++i) cout << T.get(i) << " \n"[i==W-1];
    }
};
