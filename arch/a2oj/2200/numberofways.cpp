#include "../../../l/lib.h"
// #include "../l/mod.h"

class numberofways {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<ll> P(N+1, 0);
        for (int i = 0; i < N; ++i) P[i+1] = P[i] + A[i];
        if (P[N] % 3 != 0) {
            cout << "0\n";
        } else if (P[N] == 0) {
            ll t = count(P.begin(),P.end(),0);
            cout << (t-2)*(t-3)/2 << endl;
        } else {
            int third = 0;
            ll ans = 0;
            for (int i = 0; i < N; ++i) {
                if (P[i] == P[N]/3) ++third;
                if (P[i] == 2*P[N]/3) ans += third;
            }
            cout << ans << endl;
        }

    }
};
