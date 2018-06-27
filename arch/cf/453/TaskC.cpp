#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    int N, M;
    vector<vector<int>> E;
    vector<int> R, C;
    vector<bool> V, W;

    void dfs(int u, int p) {
        if (V[u]) {
            if (W[u]) return;

            int hi = u, lo = u;
            for (int i = R.size()-1; R[i] != u; --i) {
                W[R[i]] = true;
                hi = max(hi, R[i]);
                lo = min(lo, R[i]);
            }
            C[lo] = min(C[lo], hi);

            return;
        }
        R.push_back(u);
        V[u] = true;

        for (int v:E[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        R.pop_back();
    }



void solve(istream& cin, ostream& cout) {
    cin >> N >> M;
    E.resize(N);
    C = vector<int>(N, N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    V = W = vector<bool>(N, false);
    for (int i = 0; i < N; ++i) {
        if (!V[i]) {
            dfs(i, -1);
        }
    }

    for (int i = N-1; i > 0; --i) C[i-1] = min(C[i-1], C[i]);
    vector<ll> P(N+1, 0);
    for (int i = 0; i < N; ++i) P[i+1] = P[i] + C[i];

    int Q; cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int a, b; cin >> a >> b;
        --a; --b;
        int d = bsl(a, b, [&](int c) { return C[c] > b; });

        ll ans = P[d] - P[a] + ll(b+1-d) * (b+1);
        ans -= ll(a+b)*(b-a+1)/2;
        cout << ans << '\n';
    }

}
};
