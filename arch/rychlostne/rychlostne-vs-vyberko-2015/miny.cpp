#include "../l/lib.h"
#include "../l/segtree.h"
#include "../l/consttree.h"

class miny {
public:
    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (ui t = 0; t < T; ++t) {
            ui N; cin >> N;
            vector<pair<ll,ll>> M(N);
            for (ui i = 0; i < N; ++i) cin >> M[i].x >> M[i].y;
            vector<ui> L(N), H(N);
            SetMinTree<ui> TL;
            TL.setup(N, N);
            for (ui i = 0; i < N; ++i) {
                ui l = (ui)bsl(0, (int)N-1, [&](int j) { return M[j].x + M[i].y >= M[i].x; });
                L[i] = min(l,TL.get(l,i));
                TL.put(i, L[i]);
            }

            SetMaxTree<ui> TH;
            TH.setup(N, 0);
            for (ui i = N-1; i != -1; --i) {
                ui h = (ui)bsh(0, (int)N-1, [&](int j) { return M[j].x <= M[i].x + M[i].y; });
                H[i] = max(h,TH.get(i,h));
                TH.put(i, H[i]);
            }

            ConstTree<ui,MinOp<ui>> CL(L);
            ConstTree<ui,MaxOp<ui>> CH(H);
            vector<ui> A(N);
            for (ui i = 0; i < N; ++i) {
                ui l = L[i], h = H[i], ol, oh;
                do {
                    ol = l;
                    oh = h;
                    l = CL.get(ol, oh);
                    h = CH.get(ol, oh);
                } while (l!=ol || h!=oh);
                A[i] = h - l + 1;
            }

            cout << A;
        }
    }
};
