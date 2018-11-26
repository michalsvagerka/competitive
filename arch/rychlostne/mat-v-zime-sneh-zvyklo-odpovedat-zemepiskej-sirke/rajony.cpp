#include "../l/lib.h"
// #include "../l/mod.h"

class rajony {
public:
void solve(istream& cin, ostream& cout) {
    int N, S; cin >> N >> S;
    vector<pii> T(N);
    for (int i = 0; i < N; ++i) cin >> T[i];
    sort(T.begin(),T.end());
    reverse(T.begin(),T.end());

    constexpr ll INF = 1e14;
    vector<ll> Best(S+1, INF);
    Best[S] = 0;
    ll ans = INF;
    for (int i = 0; i < N; ++i) {
        int t = T[i].x;
        int p = T[i].y;
        
        int tt = 0; ll tp = 0;
        for (int j = i+1; j < N; ++j) { tt += T[j].x; tp += T[j].y; }
        for (int j = tt; j < min(S+1, tt + t); ++j) ans = min(ans, Best[j] + tp);
        
        for (int j = t; j <= S; ++j) Best[j-t] = min(Best[j-t], Best[j] + p);
    }
    
    if (ans == INF) {
        ans = 0;
        for (pii t:T) ans += t.y;
    }

    cout << ans << '\n';
}
};
