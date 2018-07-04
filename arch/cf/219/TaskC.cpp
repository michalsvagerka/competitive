#include "../l/lib.h"
#include <numeric>
 #include "../l/consttree.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, D; cin >> N >> M >> D;
    vector<int> A(M), T(M);
    ll ans = 0;
    for (int i = 0; i < M; ++i) {
        int b;
        cin >> A[i] >> b >> T[i];
        --A[i];
        ans += b;
    }

    int t = T[0];
    vector<ll> H(N, 0), S(N);
    for (int i = 0; i < M; ++i) {
        if (t != T[i]) {
            int dd = (int)min(ll(D)*(T[i]-t), (ll)N-1);
            ConstTree<ll, MaxQOp<ll>> CT(H);

            for (int i = 0; i < N; ++i) {
                H[i] = CT.get(max(0,i-dd),min(N-1,i+dd));
            }
            t = T[i];
        }

        for (int j = 0; j < N; ++j) {
            H[j] -= abs(A[i] - j);
        }
    }

    ans += *max_element(H.begin(),H.end());
    cout << ans << '\n';
}
};
