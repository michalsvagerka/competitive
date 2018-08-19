#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<pii> S(N);
    for (int i = 0; i < N; ++i) {
        int r = 0;
        for (int j = 0; j < 4; ++j) {
            int k; cin >> k; r -= k;
        }
        S[i] = {r, i};
    }
    sort(S.begin(),S.end());
    for (int i = 0; i < N; ++i) {
        if (S[i].y == 0) {
            cout << i+1 << '\n';
            return;
        }
    }
}
};
