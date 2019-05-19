#include "../l/lib.h"
// #include "../l/mod.h"

class CIntervalGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> S(N);
        vector<int> L(N), R(N); cin >> S;
        for (int i = 0; i < N; ++i) {
            L[i] = S[i].x;
            R[i] = S[i].y;
        }
        L.push_back(0);
        R.push_back(0);
        sort(L.begin(),L.end());
        sort(R.begin(),R.end());
        reverse(L.begin(),L.end());
        vector<ll> PL(N+2, 0), PR(N+2, 0);
        for (int i = 0; i <= N; ++i) {
            PL[i+1] = PL[i] + L[i];
            PR[i+1] = PR[i] + R[i];
        }
        ll ans = 0;
        for (int k = 0; k <= N+1; ++k) {
            ans = max(ans, PL[k] - PR[k]);
        }
        cout << 2*ans << '\n';
    }
};
