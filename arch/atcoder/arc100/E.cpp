#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<pair<pii,pii>> A(1<<N);
    for (int i = 0; i < (1<<N); ++i) {
        cin >> A[i].x.x;
        A[i].x.y = i;
        A[i].y = {0,0};
    }

    for (int i = 0; i < (1<<N); ++i) {
        for (int j = 0; j < N; ++j) {
            if (i & (1<<j)) continue;
            set<pii> S;
            S.insert(A[i].x);
            S.insert(A[i].y);
            S.insert(A[i|(1<<j)].x);
            S.insert(A[i|(1<<j)].y);
            pii a = *prev(S.end());
            pii b = *prev(prev(S.end()));
            A[i|(1<<j)] = {a, b};
        }
    }

    int ans = 0;
    for (int i = 1; i < (1<<N); ++i) {
        ans = max(ans, A[i].x.x + A[i].y.x);
        cout << ans << '\n';
    }
}
};
