#include "../l/lib.h"
// #include "../l/mod.h"

class DoubleProfiles {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<vector<int>> E(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    for (int i = 0; i < N; ++i) {
        sort(E[i].begin(),E[i].end());
    }


    ll ans = 0;
    auto solve = [&](vector<vector<int>> &E) {
        sort(E.begin(),E.end());
        int i = 0;
        while (i < N) {
            int j = i+1;
            while (j < N && E[j] == E[i]) ++j;
            ans += ll(j-i) * (j-i-1) / 2;
            i = j;
        }
    };

    auto F = E;
    solve(F);

    for (int i = 0; i < N; ++i) {
        E[i].push_back(i);
        sort(E[i].begin(),E[i].end());
    }
    solve(E);

    cout << ans << endl;
}
};
