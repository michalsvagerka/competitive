#include "../l/lib.h"

class ADreamoonLikesColoring {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> L(M); cin >> L;
        ll tot = 0;
        for (int l: L) tot += l;
        if (tot < N) {
            cout << -1 << '\n';
            return;
        }

        vector<ll> Ans(M);
        for (int i = 0; i < M; ++i) {
            tot -= L[i];
            Ans[i] = min(tot+1, ll(N-i-L[i]+1));
        }

        if (*min_element(Ans.begin(),Ans.end()) <= 0) {
            cout << -1 << '\n';
            return;
        }

        cout << Ans;
    }
};
