#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    vector<vector<int>> E;

    pii dfs(int u, int p) {
        pii ans = {0, u};
        for (int v :E[u]) if (v != p) ans = max(ans, dfs(v, u));
        ans.x++;
        return ans;
    }

    bool path(int u, int p, int t, vector<int> &P) {
        if (t == u) return true;
        for (int v : E[u]) {
            if (v != p) {
                P.push_back(v);
                if (path(v, u, t, P)) return true;
                P.pop_back();
            }
        }

        return false;
    }

    bool isHog(int u, int p, int k) {
        if (k == 0) return E[u].size() == 1;

        if (E[u].size() < 3 + (p!=-1)) return false;
        for (int v : E[u]) {
            if (v != p && !isHog(v, u, k-1)) return false;
        }
        return true;
    }

void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    E.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    pii t = dfs(0, -1);
    pii s = dfs(t.y, -1);
    vector<int> P{t.y};
    path(t.y, -1, s.y, P);
    cout << (isHog(P[s.x/2], -1, K) ? "Yes" : "No") << endl;
}
};
