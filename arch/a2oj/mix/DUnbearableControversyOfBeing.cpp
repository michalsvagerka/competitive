#include "../l/lib.h"
// #include "../l/mod.h"

class DUnbearableControversyOfBeing {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<vector<int>> E(N);
    for (int i = 0; i < M; ++i) {
        int a,b; cin >> a >> b;
        --a; --b;
        E[a].push_back(b);
    }

    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        vector<int> V(N, 0);
        for (int u : E[i]) {
            for (int v: E[u]) {
                V[v]++;
            }
        }
        for (int j = 0; j < N; ++j) {
            if (i != j) {
                ans += V[j]*(V[j]-1)/2;
            }
        }
    }
    cout << ans << endl;
}
};
