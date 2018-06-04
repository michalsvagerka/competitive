#include "../../../l/lib.h"
#include "../../../l/graph.h"
#include "../../../l/fenwick.h"

class territory {
public:
    int N;
    Tree T;
    int tot = 0;
    vector<int> Enter, Exit, Preorder;
    vector<bool> V;

    void dfs(int u, int &t) {
        Preorder[t] = u;
        Enter[u] = t++;
        for (int v: T.neighbors(u)) {
            if (v != T.parent(u)) {
                dfs(v, t);
            }
        }
        Exit[u] = t-1;
    }

    bool iscovered(Fenwick<int> & F, int w) {
        int cur = F.range(Enter[w],Exit[w]);
        if (V[w]) return true;
        if (cur == 0) return false;
        if (cur < tot) return true;
        int l = bsl(Enter[w],Exit[w],[&](int c){return F.range(Enter[w],c) > 0;});
        int r = bsh(Enter[w],Exit[w],[&](int c){return F.range(c,Exit[w]) > 0;});
        return T.lca(Preorder[l],Preorder[r]) == w;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        T = Tree(N);
        for (int i = 0; i < N - 1; ++i) {
            int u,v; cin >> u >> v;
            T.addEdge(u,v);
        }

        T.calcLA();
        Enter.resize(N); Exit.resize(N); Preorder.resize(N);
        int time = 0;
        dfs(T.root(), time);
        Fenwick<int> F(N, 0);
        V = vector<bool>(N, false);

        int E; cin >> E;
        for (int e = 0; e < E; ++e) {
            int t; cin >> t;
            if (t == 0) {
                int v; cin >> v;
                if (V[v]) {
                    V[v] = false;
                    F.add(Enter[v], -1);
                    tot--;
                } else {
                    V[v] = true;
                    F.add(Enter[v], 1);
                    tot++;
                }

            } else {
                int u, v; cin >> u >> v;
                int w = T.lca(u,v);
                int a = 0;
                if (tot > 0 && F.range(Enter[w], Exit[w]) > 0) {
                    bool nonEmpty = false;
                    set<int> cnd;
                    for (int z: {u, v}) {
                        int r = z;
                        for (int i = T.logN-1; i >= 0; --i) {
                            int s = T.PP[i][r];
                            if (s != -1 && F.range(Enter[s],Exit[s]) == 0) {
                                r = s;
                            }
                        }

                        if (F.range(Enter[r],Exit[r]) == 0) r = T.parent(r);
                        a += T.D[r];
                        int g = r;
                        for (int i = T.logN-1; i >= 0; --i) {
                            int s = T.PP[i][r];
                            if (s != -1 && T.depth(s) >= T.depth(w) && F.range(Enter[s],Exit[s]) < tot) {
                                r = s;
                            }
                        }

                        if (r != w && F.range(Enter[r],Exit[r]) < tot) r = T.parent(r);

                        a -= T.D[r];
                        cnd.insert(r);
                    }

                    for (int c:cnd) {
                        a += iscovered(F,c);
                    }
                    cout << a << '\n';
                } else {
                    cout << 0 << '\n';
                }
            }
        }
    }
};
