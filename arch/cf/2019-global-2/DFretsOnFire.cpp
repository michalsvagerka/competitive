#include "../l/lib.h"

class DFretsOnFire {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> S(N); cin >> S;
        sort(S.begin(),S.end());
        for (int i = 0; i < N-1; ++i) S[i] = S[i+1] - S[i];
        S[N-1] = 1000000000000000005LL;
        sort(S.begin(),S.end());
        vector<ll> P(N+1, 0LL);
        for (int i = 0; i < N; ++i) {
            P[i+1] = P[i] + S[i];
        }

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            ll l, r; cin >> l >> r;
            ll len = r - l + 1;
            int i = bsh(0, N-1, [&](int x) { return S[x] <= len; });
            cout << P[i+1] + (N-i-1)*len << ' ';
        }
        cout << endl;
    }
};
