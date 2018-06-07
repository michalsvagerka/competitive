#include "../l/lib.h"

class lostborn {
public:
    vector<vector<ll>> C;
    vector<int> A;

    ll ans(int i, ll S) {
        if (i == A.size() || S == 0) return S;
        if (S < 100000 && C[i][S] != -1) return C[i][S];
        else {
            ll x = ans(i+1, S) - ans(i+1, S/A[i]);
            if (S < 100000) C[i][S] = x;
            return x;
        }
    }

    void solve(istream& cin, ostream& cout) {
        ll N; int K; cin >> N >> K;
        A.resize(K);
        cin >> A;
        sort(A.begin(),A.end());
        reverse(A.begin(),A.end());
        C = vector2<ll>(K, 100000, -1);
        cout << ans(0, N) << '\n';
    }
};
