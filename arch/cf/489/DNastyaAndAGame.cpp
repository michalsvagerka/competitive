#include "../../../l/lib.h"
#include "../../../l/segtree.h"

constexpr ll INF = 2e18;
struct CappedMultiplyOp { ll operator()(ll a, ll b) { return a>=INF/b?INF:a*b; }};
using MulTree = SegTree<ll, CappedMultiplyOp>;


class DNastyaAndAGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<ll> A(N); cin >> A;
        vector<ll> S(N+1, 0);
        for (int i = 0; i < N; ++i) S[i+1] = S[i] + A[i];
        vector<int> Next(N, N);
        for (int i = N-1; i > 0; --i) {
            if (A[i] == 1) {
                Next[i-1] = Next[i];
            } else {
                Next[i-1] = i;
            }
        }

        ll ans = 0;
        MulTree T;
        T.setup(A,1);
        for (int i = 0; i < N; ++i) {
            int j = i;
            while (j < N) {
                ll prod = T.get(i, j);
                ll sum = S[j+1] - S[i];
                if (prod == K*sum) ans++;
                if (prod == INF || j == N-1) break;
                if (prod <= K*sum) {
                    j = Next[j];
                } else {
                    int k = bsl(j+1, N-1, [&](int x) {
                        return K*(S[x+1] - S[i]) >= prod;
                    });
                    if (k == -1) break;
                    j = k;
                }
            }
        }
        cout << ans << '\n';
    }
};
