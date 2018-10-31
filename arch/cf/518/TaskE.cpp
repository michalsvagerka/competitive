#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> F;

class TaskE {
public:
    int N;
    vector<vector<int>> E;
    vector<int> S;

    int size(int u, int p) {
        S[u] = 1;
        for (int v:E[u]) if (v!=p) S[u] += size(v,u);
        return S[u];
    }

    F ans;

    pair<F, F> dfs(int u, int p) {
        F notAvailable = 1;
        F available = F{2}.pow(S[u]-1);

        for (int v : E[u]) {
            if (v != p) {
                auto x = dfs(v, u);
                notAvailable *= x.x + x.y + x.y;
            }
        }
        available -= notAvailable;
        ans += available * F{2}.pow(N-S[u]);

//        cerr << u+1 << ' ' << notAvailable << ' ' << available << endl;
        return {notAvailable, available};
    }

void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(N);
    S.resize(N);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    ans = 0;
    size(0, -1);
    dfs(0, -1);
    cout << 2*ans << endl;
}
};
