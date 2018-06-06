#include "../../../l/lib.h"
// #include "../l/mod.h"

class gameontree {
public:
    int N;
    double ans;
    vector<vector<int>> E;

    void calc(int u, int p, int d) {
        ans += 1.0/d;
        for (int v:E[u]) if (v!=p) calc(v, u, d+1);
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        calc(0, -1, 1);
        cout << fixed << setprecision(15) << ans << endl;
    }
};
