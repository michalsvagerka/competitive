#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<unordered_set<int>> E(N);
        vector<int> C(N);
        vector<pii> M;
        for (int i = 0; i < 2*N-2; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            if (E[u].count(v) == 1) {
                E[u].erase(v);
                E[v].erase(u);
                M.emplace_back(u,v);
            } else {
                E[u].insert(v);
                E[v].insert(u);
            }
        }

        vector<set<int>> D(N);
        for (int i = 0; i < N; ++i) { C[i] = i; D[i].insert(i); }

        for (int m = 0; m < M.size(); ++m) {
            int u = C[M[m].x];
            int v = C[M[m].y];
            if (D[u].size() < D[v].size()) swap(u,v);
            for (int w: D[v]) {
                D[u].insert(w);
                C[w] = u;
            }

            for (int w: E[v]) {
                E[w].erase(v);
                if (E[u].count(w) == 1) {
                    E[u].erase(w);
                    E[w].erase(u);
                    M.emplace_back(u,w);
                } else {
                    E[u].insert(w);
                    E[w].insert(u);
                }
            }

            E[v].clear();
            D[v].clear();
        }

        cout << (M.size() == N-1 ? "YES" : "NO") << endl;
    }
};
