#include "../l/lib.h"
 #include "../l/mod.h"
#include "../l/segtree.h"

class TaskC {
public:

    int N, T;
    vector<vector<int>> E;
    vector<int> D, Enter, Exit;

    void dfs(int u, int d) {
        Enter[u] = T++;
        D[u] = d;
        for (int v:E[u]) dfs(v, d+1);
        Exit[u] = T;
    }

void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(N);
    D.resize(N);
    Enter.resize(N);
    Exit.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int p; cin >> p;
        E[p-1].push_back(i+1);
    }

    T = 0;
    dfs(0, 0);

    AddSumTree<FieldMod> A, B;
    A.setup(N, 0);
    B.setup(N, 0);

    int Q; cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int t, v; cin >> t >> v;
        --v;
        if (t == 1) {
            FieldMod x, k; cin >> x >> k;
            A.put(Enter[v], Exit[v]-1, -k);
            B.put(Enter[v], Exit[v]-1, x + k * D[v]);
        } else {
            FieldMod a = A.get(Enter[v]);
            FieldMod b = B.get(Enter[v]);
//            cout << v << ' ' << a << ' ' << b << ' ' << D[v] << ' ';
            cout << (a * D[v] + b) << '\n';
        }
    }
}
};
