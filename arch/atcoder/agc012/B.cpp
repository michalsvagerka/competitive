#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    vector2<bool> Z;
    vector<int> Ans;
    vector<vector<int>> E;

    void color(int v, int d, int c) {
//        cerr << v << ' ' << d << ' ' << c << endl;
        if (Z[v][d]) return;

        for (int i = 0; i <= d; ++i) Z[v][d] = true;
        if (!Ans[v]) Ans[v] = c;
        if (d > 0) {
            for (int u:E[v]) {
                color(u, d-1, c);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, M, Q; cin >> N >> M;
        E.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        cin >> Q;
        vector<int> D(Q), V(Q), C(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> V[i] >> D[i] >> C[i];
//            cerr << V[i] << ' ' << D[i] << ' ' << C[i] << endl;
        }

        Ans = vector<int>(N, 0);
        Z = vector2<bool>(N, 11, false);
        for (int i = Q-1; i >= 0; --i) {
            color(V[i]-1,D[i],C[i]);
        }

        for (int a:Ans) cout << a << '\n';
    }
};
