#include "../../../l/lib.h"
#include "../../../l/graph.h"

class foolsandroads {
public:
    int N;
    vector<vector<pii>> E;
    vector<int> V, A;

    int dfs(int u, int p) {
        int s = V[u];
        for (pii v:E[u]) {
            if (v.x!=p) {
                int x = dfs(v.x, u);
                A[v.y] = x;
                s += x;
            }
        }
        return s;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        Tree T(N);
        V = vector<int>(N, 0);
        A.resize(N-1);
        for (int i = 0; i < N-1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back({v,i});
            E[v].push_back({u,i});
            T.addEdge(u,v);
        }

        int K; cin >> K;
        for (int i = 0; i < K; ++i) {
            int u,v; cin >> u >> v;
            --u; --v;
            V[u]++;
            V[v]++;
            V[T.lca(u,v)] -= 2;
        }

        dfs(0, -1);
        cout << A;
    }
};
