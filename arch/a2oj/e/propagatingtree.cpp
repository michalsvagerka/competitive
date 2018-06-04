#include "../../../l/lib.h"
#include "../../../l/segtree.h"

class propagatingtree {
public:
    vector<vector<int>> E;
    vector<int> Enter, Exit, Depth;
    int t;

    void dfs(int u, int p, int d) {
        Enter[u] = t++;
        Depth[u] = d;
        for (int v:E[u]) if (v!=p) dfs(v,u,d+1);
        Exit[u] = t;
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        E.resize(N);
        Enter.resize(N);
        Exit.resize(N);
        Depth.resize(N);

        for (int i = 0; i < N-1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        t = 0;
        dfs(0, -1, 0);
        vector<int> S(N);
        for (int i = 0; i < N; ++i) S[Enter[i]] = A[i];

        AddMinTree<int> T[2];
        T[0].setup(S);
        T[1].setup(S);

        for (int q = 0; q < M; ++q) {
            int t,x; cin >> t >> x; --x;
            int d = Depth[x]%2;
            if (t == 1) {
                int v; cin >> v;
                T[d].put(Enter[x], Exit[x]-1, v);
                T[1-d].put(Enter[x], Exit[x]-1, -v);
            } else {
                cout << T[d].get(Enter[x]) << '\n';
            }
        }
    }
};
