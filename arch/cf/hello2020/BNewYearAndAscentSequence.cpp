#include "../l/lib.h"

class BNewYearAndAscentSequence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<vector<int>> S(N);
        for (int i = 0; i < N; ++i) {
            int s; cin >> s;
            S[i].resize(s);
            cin >> S[i];
        }

        vector<pii> NoAsc;
        for (int i = 0; i < N; ++i) {
            bool asc = false;
            for (int j = 0; j < S[i].size()-1; ++j) {
                asc |= S[i][j+1] > S[i][j];
            }
            if (!asc) {
                NoAsc.push_back({S[i][0], S[i].back()});
            }
        }
        sort(NoAsc.begin(),NoAsc.end());
        vector<int> Q(1000001, 0);
        for (pii x: NoAsc) Q[x.x]++;
        for (int i = 0; i < 1000000; ++i) Q[i+1] += Q[i];
        ll ans = ll(N)*N;
        for (pii x: NoAsc) ans -= Q[x.y];
        cout << ans << '\n';
    }
};
