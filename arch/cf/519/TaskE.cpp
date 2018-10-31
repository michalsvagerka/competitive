#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<ll> Ans(N, 0);
    vector<int> X(N), Y(N);
    vector<pii> D(N);
    ll sumB = 0;
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
        D[i] = {X[i]-Y[i], i};
        sumB += Y[i];
    }

    sort(D.begin(),D.end());

    ll sumD = 0;
    for (int i = 0; i < N; ++i) {
        int j = D[i].y;
        Ans[j] += sumD + ll(N-i-1) * D[i].x + ll(N-1) * Y[j] + (sumB - Y[j]);
        sumD += D[i].x;
    }

    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        int cost = min(X[u] + Y[v], Y[u] + X[v]);
        Ans[u] -= cost;
        Ans[v] -= cost;
    }

    cout << Ans;

}
};
