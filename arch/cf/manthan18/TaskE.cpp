#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> M >> K;
    vector<pii> F(M); cin >> F;

    vector<set<int>> E(N);
    for (pii&f:F) {
        --f.x; --f.y;
        E[f.x].insert(f.y);
        E[f.y].insert(f.x);
    }

    set<pii> D;
    for (int i = 0; i < N; ++i) {
        D.insert({E[i].size(),i});
    }

    vector<int> Ans(M);
    for (int i = M-1; i >= 0; --i) {
        while (!D.empty() && D.begin()->x < K) {
            int u = D.begin()->y;
            D.erase(D.begin());
            for (int v: E[u]) {
                D.erase({E[v].size(), v});
                E[v].erase(u);
                D.insert({E[v].size(), v});
            }
            E[u].clear();
        }

        Ans[i] = D.size();
        int u = F[i].x;
        int v = F[i].y;
        if (E[u].size() >= K && E[v].size() >= K) {
            D.erase({E[u].size(), u});
            D.erase({E[v].size(), v});
            E[u].erase(v);
            E[v].erase(u);
            D.insert({E[u].size(), u});
            D.insert({E[v].size(), v});
        }
    }

    for (int a: Ans) cout << a << '\n';
}
};
