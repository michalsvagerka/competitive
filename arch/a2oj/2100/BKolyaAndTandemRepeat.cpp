#include "../l/lib.h"

class BKolyaAndTandemRepeat {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int K; cin >> K;
        int N = S.size();
        if (K >= N) {
            cout << (K+N) - (K+N)%2 << endl;
            return;
        }

        int ans = K;
        for (int l = 1; 2*l + K <= N; ++l) {
            bool ok = true;
            for (int i = 0; i < l; ++i) {
                ok &= S[N-i-1] == S[N-i-1-K-l];
            }
            if (ok) ans = max(ans, l + K);
            
        }

        for (int i = 0; i < N; ++i) {
            for (int l = 1; l < N; ++l) {
                bool ok = true;
                for (int j = 0; j < l; ++j) {
                    ok &= i+l+j < N+K && (i+l+j >= N || S[i+j] == S[i+j+l]);
                }
                if (ok) ans = max(ans,l);
            }
        }

        cout << 2*ans << endl;
    }
};
