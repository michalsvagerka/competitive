#include "../l/lib.h"

class BBornThisWay {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        ll TA, TB; cin >> TA >> TB;
        int K; cin >> K;
        if (K >= min(N,M)) {
            cout << "-1\n"; return;
        }


        vector<ll> A(N), B(M); cin >> A >> B;
        int l = 0;
        ll ans = 0;
        for (int k = 0; k <= K; ++k) {
            ll arr = A[k] + TA;
            while (l < M && B[l] < arr) ++l;
            int r = l + K - k;
            if (r >= M) {
                cout << "-1\n"; return;
            }
            ans = max(ans, B[r] + TB);
        }
        cout << ans << endl;
    }
};
