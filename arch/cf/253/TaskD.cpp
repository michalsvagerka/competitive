#include "../l/lib.h"
#include "../l/graph.h"
class TaskD {
public:
    int N, T;
    Tree W;
    vector<vector<int>> E;
    vector<int> Enter;

    void preorder(int u) {
        Enter[u] = T++;
        for (int v:E[u]) {
            preorder(v);
            W.addEdge(Enter[u], Enter[v]);
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        Enter.resize(N+1);
        T = 0;
        E.resize(N+1);
        W = Tree(N+1);
        for (int i = 0; i < N; ++i) {
            int p; cin >> p;
            E[p-1].push_back(i+1);
        }

        preorder(0);
        W.calcLA();

//        vector<set<int>> Occ(1);
        int ans = 1;

        vector<int> Ans;
        vector<int> Val(N+1, 0);
        vector<pii> F(N+1, {0,0});
        int c = 0;
        for (int i = 1; i <= N; ++i) {
            Val[Enter[i]] = 1;
            int g = W.parent(Enter[i]);
            int v = 1;
            while (g != 0) {
                int a = F[g].x;
                int b = F[g].y;
                if (v > a) { b = a; a = v; }
                else if (v > b) { b = v; }
                F[g] = {a,b};
                v = max(a, b+1);
                if (v != Val[g]) {
                    Val[g] = v;
                    ans = max(ans, v);
                    g = W.parent(g);
                } else {
                    break;
                }
            }
//            while (g != 0) {
//                c++;
//                if (Val[g] == v) break;
//                Val[g] = v;
//
//                if (Occ.size() <= v) Occ.push_back({});
//                auto it = Occ[v].insert(g).x;
//
//                int l1 = -1, l2 = -1;
//                if (it != Occ[v].begin()) {
//                    auto pit = prev(it);
//                    l1 = W.lca(*pit, g);
//                    if (l1 == *pit) {
//                        Val[*pit] = 0;
//                        Occ[v].erase(pit);
//                        if (it != Occ[v].begin()) l1 = W.lca(*prev(it), g); else l1 = -1;
//                    }
//                }
//
//                auto nit = next(it);
//                if (nit != Occ[v].end()) {
//                    l2 = W.lca(*nit, g);
//                    if (W.isAncestor(g, *nit)) {
//                        Val[g] = 0;
//                        Occ[v].erase(it);
//                        break;
//                    }
//                }
//
//                if (l1 == -1 && l2 == -1) break;
//                if (l1 == -1) swap(l1, l2);
//                else if (l2 != -1 && W.depth(l1) < W.depth(l2)) swap(l1, l2);
//
//                if (g == l1) break;
//                g = l1;
//                ++v;
//            }

            Ans.push_back(ans);
        }
//        int r = 0;
//        for (int i = 0; i <= N; ++i) r += Val[i];
//        cout << r << ' ' << c << endl;
//        cout << Ans.back();
        cout << Ans << '\n';
//        cout << Ans;
    }
};
