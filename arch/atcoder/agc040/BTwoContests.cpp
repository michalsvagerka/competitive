#include "../l/lib.h"

class BTwoContests {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;
        vector<pii> X(N); cin >> X;
        sort(X.begin(),X.end());
        vector<pii> Pref(N+1), Suf(N+1);
        Pref[0] = {1,1000000000};
        for (int i = 0; i < N; ++i) {
            Pref[i+1] = {max(Pref[i].x, X[i].x), min(Pref[i].y, X[i].y)};
        }
        Suf[N] = {1,1000000000};
        for (int i = N-1; i >= 0; --i) {
            Suf[i] = {max(Suf[i+1].x, X[i].x), min(Suf[i+1].y, X[i].y)};
        }

        int ans = 0;
        for (int i = 1; i < N; ++i) {
            if (Pref[i].y >= Pref[i].x && Suf[i].y >= Suf[i].x) {
                ans = max(ans, Pref[i].y - Pref[i].x + 1 + Suf[i].y - Suf[i].x + 1);
            }
        }
        int all = max(Pref[N].y - Pref[N].x + 1, 0);
        for (int i = 0; i < N; ++i) {
            ans = max(ans, X[i].y - X[i].x + 1 + all);
        }
        cout << ans << '\n';
    }
};
