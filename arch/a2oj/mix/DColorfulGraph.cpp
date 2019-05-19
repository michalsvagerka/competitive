#include "../l/lib.h"
// #include "../l/mod.h"

class DColorfulGraph {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<int> C(N); cin >> C;
    map<int, set<int>> T;
    for (int i = 0; i < N; ++i) {
        T[C[i]].insert(C[i]);
    }
    for (int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        T[C[a]].insert(C[b]);
        T[C[b]].insert(C[a]);
    }

    int best = 0;
    int ans = 0;
    for (auto &t: T) {
        if (t.y.size() > best) {
            best = t.y.size();
            ans = t.x;
        }
    }
    cout << ans << '\n';
}
};
