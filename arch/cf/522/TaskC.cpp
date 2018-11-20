#include "../l/lib.h"
 #include "../l/mod.h"

 typedef Field<998244353> F;

class TaskC {
public:
    vector<vector<int>> E;

    void dfs(int u, int p, F *one, F *odd, F *even) {
        *one = 1;
        *odd = 0;
        *even = 0;

        for (int v:E[u]) {
            if (p != v) {
                F a, b, c;
                dfs(v, u, &a, &b, &c);
                F cut = a + c;
                F d = *one * cut;
                F e = *one * c + *odd * cut + *odd * c;
                F f = (*one + *odd) * (a + b) + *even * c + *even * cut;

                *one = d;
                *odd = e;
                *even = f;
            }
        }

    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        F a, b, c;
        dfs(0, -1, &a, &b, &c);
        cout << a + c << endl;
    }
};
