#include "../l/lib.h"
 #include "../l/primes.h"

class gcdcount {
public:
void solve(istream& cin, ostream& cout) {
    int N, A, B;
    cin >> N >> A >> B;
    
    Moebius M(N);
    vector<ll> C(N+1, 0), D(N+1, 0);
    for (int i = N; i >= 1; --i) {
        C[i] = ll(N/i) * ll(N/i);
        for (pii m: M) {
            if (m.x * i > N) break;
            D[i] += m.y * C[m.x * i];
        }
    }
    
    ll ans = 0;
    for (int i = A; i <= B; ++i) {
        ans += D[i];
    }
    cout << ans << endl;

}
};
