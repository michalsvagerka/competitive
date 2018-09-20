#include "../l/lib.h"
 #include "../l/primes.h"

class D {
public:
void solve(istream& cin, ostream& cout) {
    auto P = Sieve{10000}.primes();
    int N; cin >> N;
    vector<int> R(2*N+4);
    for (int i = 0; i < N+2; ++i) {
        R[2*i] = P[i];
        R[2*i+1] = P[N+2+i];
    }
    
    int x = N%2;
    
    vector2<ll> A(N, N, -1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i%2 == j%2) {
                A[i][j] = R[1+i+j] * R[N+i-j+x];
            } else {
                A[i][j] = 1LL * R[i+j] * R[i+j+2] * R[N+i-j-1+x] * R[N+i-j+1+x] + 1;
            }
        }
    }
    
//    ll mx = 0;
//    for (auto&a:A) for (ll&aa:a) mx = max(mx, aa);
///
//    cout << mx;
    for (auto&a:A) cout << a;
}
};
