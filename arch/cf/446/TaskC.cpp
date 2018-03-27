#include "../../../l/lib.h"
#include "../../../l/util.h"
// #include "../l/mod.h"

class TaskC {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        map<int,vector<int>> E;
        vector<pair<pii,int>> F(M);

        for (int i = 0; i < M; ++i) {
            int u,v,w; cin >> u >> v >> w;
            --u; --v;
            E[w].push_back(i);
            F[i] = {{u,v}, w};
        }

        int Q; cin >> Q;
        vector<bool> Ans(Q, true);
        map<int, map<int, vector<int>>> QQ;

        for (int q = 0; q < Q; ++q) {
            int c; cin >> c;
            vector<int> I(c); cin >> I;
            for (int &i:I) {
                --i;
                QQ[F[i].y][q].push_back(i);
            }
        }

        UnionFind U(N);
        for (auto &e:E) {
            for (auto &&qq:QQ[e.x]) {
                int q = qq.x;
                set<int> V;
                for (int f: qq.y) {
                    V.insert(U.find(F[f].x.x));
                    V.insert(U.find(F[f].x.y));
                }
                map<int,int> W; int k = 0;
                for (int v:V) W[v] = k++;
                UnionFind UF(k);
                for (int f: qq.y) {
                    Ans[q] = Ans[q] && UF.unite(W[U.find(F[f].x.x)], W[U.find(F[f].x.y)]);
                }
            }


            for (int f:e.y) {
                U.unite(F[f].x.x, F[f].x.y);
            }
        }

        for (int q = 0; q < Q; ++q) cout << (Ans[q] ? "YES\n" : "NO\n");
    }
};
