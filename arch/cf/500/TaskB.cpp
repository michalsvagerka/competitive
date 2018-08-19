#include "../l/lib.h"
 #include "../l/util.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, Q; cin >> N >> M >> Q;
    vector<pii> C(Q); cin >> C;
    vector<bool> A(N, false), B(M, false);
    for (pii c:C) {
        A[c.x-1] = true;
        B[c.y-1] = true;
    }

    vector<vector<int>> D(N), E(M);
    for (pii c:C) {
        D[c.x-1].push_back(c.y-1);
        E[c.y-1].push_back(c.x-1);
    }

    UnionFind F(N), G(M);
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < D[i].size(); ++j) {
            G.unite(D[i][0], D[i][j]);
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 1; j < E[i].size(); ++j) {
            F.unite(E[i][0], E[i][j]);
        }
    }

    int z = max(count(A.begin(),A.end(),false),count(B.begin(),B.end(),false));

    int ans = max(N, M);
    ans = min(ans,(int)G.comp-1);
    ans = min(ans,(int)F.comp-1);
    ans += z;

    cout << ans << endl;
}
};
