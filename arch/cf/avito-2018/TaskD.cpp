#include "../l/lib.h"
#include "../l/util.h"

class TaskD {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, K; cin >> N >> M >> K;
        vector<pair<int, pii>> E;
        vector<int> X(K); cin >> X;
        for (int &x: X) --x;
        for (int i = 0; i < M; ++i) {
            int u, v, w; cin >> u >> v >> w;
            E.push_back({w,{u-1,v-1}});
        }
        sort(E.begin(),E.end());

        UnionFind UF(N);
        int j = 1;
        for (auto &e: E) {
            if (UF.unite(e.y.x, e.y.y)) {
                while (j < K && UF.united(X[0], X[j])) ++j;
                if (j == K) {
                    cout << vector<int>(K, e.x);
                    return;
                }
            }
        }
    }
};
