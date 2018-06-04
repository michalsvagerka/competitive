#include "../../../l/lib.h"
#include "../../../l/segtree.h"

class watertree {
public:

    int N, t;
    vector<vector<int>> E;
    vector<int> Enter,Exit;

    void dfs(int u, int p) {
        Enter[u] = t++;
        for (int v:E[u]) if (v!=p) dfs(v,u);
        Exit[u] = t;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        Enter.resize(N);
        Exit.resize(N);
        t = 0;

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1);
        AssignMaxTree<int> T1, T2;

        T1.setup(N, 0);
        T2.setup(N, 0);

        int Q; cin >> Q;
        for (int q = 1; q <= Q; ++q) {
            int t, u; cin >> t >> u; --u;
            if (t == 1) {
                T1.put(Enter[u], Exit[u]-1, q);
            } else if (t == 2) {
                T2.put(Enter[u], q);
            } else {
                int a = T1.get(Enter[u]);
                int b = T2.get(Enter[u], Exit[u]-1);
                cout << (a > b) << '\n';
            }
        }


    }
};
