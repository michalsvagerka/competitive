#include "../../../l/lib.h"
#include "../../../l/fenwick.h"

class enemyisweak {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;

        vector<int> B = A; sort(B.begin(),B.end());
        map<int,int> C;
        for (int i = 0; i < N; ++i) C[B[i]] = i;
        for (int &a: A) a = C[a];

        ll ans = 0;
        Fenwick<ll> F(N, 0), G(N, 0);
        for (int i = 0; i < N; ++i) {
            ans += G.range(A[i] + 1, N - 1);
            G.add(A[i], F.range(A[i] + 1, N - 1));
            F.add(A[i], 1);
        }

        cout << ans << '\n';
    }
};
