#include "../../../l/lib.h"
#include "../../../l/consttree.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<int> D(N), H(N); cin >> D >> H;

    vector<pair<ll,int>> A(2*N), B(2*N);
    ll d = 0;
    for (int i = 0; i < 2*N; ++i) {
        A[i] = {2*H[i%N] + d, i};
        B[i] = {2*H[i%N] - d, i};
        d += D[i%N];
    }

    ConstTree<pair<ll,int>, MaxQOp<pair<ll,int>>> E(A), F(B);
    for (int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        int s, t;
        if (a <= b) { s = b+1; t = a+N-1; }
        else { s = b+1; t = a-1; }
        ll ans = 0;
        auto hi = E.get(s,t);
        if (hi.y != s) {
            auto lo = F.get(s,hi.y-1);
            ans = hi.x + lo.x;
        }

        hi = F.get(s, t);
        if (hi.y != t) {
            auto lo = E.get(hi.y+1, t);
            ans = max(hi.x + lo.x, ans);
        }
        cout << ans << '\n';
    }
}
};
