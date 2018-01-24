#include "../l/lib.h"
// #include "../l/mod.h"

class policia {
public:
    vector<vector<int>> E;
    vector<bool> M;
    int ans;

    bool solve(int u, int p) {
        int c = M[u];
        for (int v:E[u]) c += (v!=p) && solve(v,u);
        ans += c>1;
        return c==1;
    }

    void solve(istream& cin, ostream& cout) {
        ui N,C; cin >> N >> C;
        E.resize(N);
        M=vector<bool>(N,false);
        for (int i = 0; i < N - 1; ++i) {
            int a,b; cin >> a >> b;
            --a; --b;
            E[a].push_back(b);
            E[b].push_back(a);
        }

        for (int i = 0; i < C; ++i) {
            int a; cin >> a; --a;
            M[a] = true;
        }

        ans = 0;
        solve(0, -1);
        cout << ans << endl;
    }
};
