#include "../../../l/lib.h"
#include "../../../l/bridges.h"
#include "../../../l/util.h"

class EWeNeedMoreBosses {
public:
    pii diam(const vector<vector<int>> &E, int u, int p) {
        pii d = {0, u};
        for (int v : E[u]) {
            if (v != p) {
                d = max(d, diam(E, v, u));
            }
        }
        d.x++;
        return d;
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int u,v;cin>>u>>v;
            --u;--v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        Graph G(E);
        vector<pii> br;
        G.bridges(br);
        if (br.size() == 0) {
            cout << 0 << '\n';
            return;
        }
        for (pii&b:br) if (b.x > b.y) swap(b.x, b.y);
        set<pii> bb{br.begin(),br.end()};
        UnionFind UF(N);
        for (int i = 0; i < N; ++i) {
            for (int j : E[i]) {
                if (i < j && bb.count({i,j}) == 0) UF.unite(i,j);
            }
        }

        vector<vector<int>> F(N);
        for (pii b: br) {
            int u = UF.find(b.x), v = UF.find(b.y);
            F[u].push_back(v);
            F[v].push_back(u);
        }

        int root = 0;
        while (F[root].empty()) ++root;
        auto f = diam(F, root, -1);
        auto g = diam(F, f.y, -1);
        cout << g.x-1 << endl;
    }
};
