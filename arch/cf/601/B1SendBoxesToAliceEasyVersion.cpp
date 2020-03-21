#include "../l/lib.h"

constexpr ll MX = 1e18;

class B1SendBoxesToAliceEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> O;
        for (int i = 0; i < N; ++i) {
            if (A[i] == 1) O.push_back(i);
        }
        ll ans = MX;
        int M = O.size();
        vector<ll> P(M+1, 0);
        for (int i = 0; i < M; ++i) P[i+1] = P[i] + O[i];
        for (int j = 2; j <= N; ++j) {
            if (M%j!=0) continue;
            ll cur = 0;
            for (int i = 0; i < M; i+=j) {
                int k = i+j-1;
                int med = (i+k)/2;
                cur += (P[k+1] - P[med+1]) - ll(k-med) * O[med]  + ll(med - i) * O[med] - (P[med] - P[i]);
            }
            ans = min(ans, cur);
        }
        
        if (ans == MX) cout << -1 << endl;
        else cout << ans << endl;
    }
};
