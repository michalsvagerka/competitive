#include "../../../l/lib.h"

class AConnectionAndDisconnection {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        ll K; cin >> K;
        vector<int> C{1};
        int N = S.size();
        for (int i = 1; i < N; ++i) {
            if (S[i] == S[i-1]) C.back()++;
            else C.push_back(1);
        }

        int M = C.size();
        if (M == 1) {
            cout << N * K / 2 << endl;
        } else {
            ll ans = 0;
            for (int i = 0; i < M; ++i) {
                ans += K * (C[i]/2);
            }
            if (S[0] == S[N-1]) {
                ans += (K - 1) * ((C[0] + C[M - 1]) / 2 - C[0]/2 - C[M-1]/2);
            }
            cout << ans << endl;
        }
    }
};
