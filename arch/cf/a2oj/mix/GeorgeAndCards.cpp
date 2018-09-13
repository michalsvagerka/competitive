#include "../l/lib.h"
#include "../l/segtree.h"
#include "../l/fenwick.h"

class GeorgeAndCards {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    vector<int> P(N); cin >> P;
    for (int &p:P) --p;
    vector<int> B(K); cin >> B;
    for (int &b:B) --b;
    vector<bool> U(N, false);
    for (int b:B) U[b] = true;

    vector<int> L(N, -1), H(N, -1), I(N, -1);
    SetMaxTree<int> T;
    T.setup(N+1, 0);
    for (int i = 0; i < N; ++i) {
        if (U[P[i]]) {
            T.put(P[i]+1, i+1);
        } else {
            I[P[i]] = i;
            L[P[i]] = T.get(0, P[i]);
        }
    }

    SetMinTree<int> TT;
    TT.setup(N+1, N);
    for (int i = N-1; i >= 0; --i) {
        if (U[P[i]]) {
            TT.put(P[i]+1, i);
        } else {
            H[P[i]] = TT.get(0, P[i]);
        }
    }


    Fenwick<int> F(N, 0);
    for (int i = 0; i < N; ++i) F.add(i, 1);
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        if (!U[i]) {
            ans += F.range(L[i], H[i]-1);
            F.add(I[i], -1);
        }
    }
    cout << ans << endl;
}
};
