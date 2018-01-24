#include "../l/lib.h"
// #include "../l/mod.h"

class fleacircus {
public:
    int ans;
    int cnt;
    vector<vector<int>> E;

    void dfs(int u, int d) {
        ans = max(ans, d);
        ++cnt;
        for (int v: E[u]) dfs(v, d+1);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int r = -1;
        E.resize(N);
        for (int i = 0; i < N; ++i) {
            int a; cin >> a; --a;
            if (a == i) {
                if (r == -1) {
                    r = a;
                } else {
                    cout << "-1\n";
                    return;
                }
            } else {
                E[a].push_back(i);
            }
        }

        if (r == -1) {
            cout << "-1\n";
            return;
        }

        ans = 0; cnt = 0;
        dfs(r, 0);
        if (cnt < N) {
            cout << "-1\n";
        } else {
            cout << ans << endl;
        }
    }
};
