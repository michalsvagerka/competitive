#include "../../../l/lib.h"
#include "../../../l/util.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        if (N-1-M > N/2) {
            cout << "Impossible\n";
            return;
        }
        if (M == N-1) {
            cout << 0 << endl;
            return;
        }

        vector<int> A(N); cin >> A;
        UnionFind U(N);
        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b;
            U.unite(a,b);
        }

        map<int, vector<int>> Z;
        for (int i = 0; i < N; ++i) {
            Z[U.find(i)].push_back(A[i]);
        }

        vector<int> Q;
        ll ans = 0;
        for (auto &z:Z) {
            sort(z.y.begin(),z.y.end());
            ans += z.y[0];
            copy(z.y.begin()+1, z.y.end(), back_inserter(Q));
        }

        sort(Q.begin(),Q.end());
        for (int i = 0; i < Z.size()-2; ++i) ans += Q[i];
        cout << ans << endl;
    }
};
