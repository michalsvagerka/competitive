#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    ll N, K; cin >> N >> K;
    ll lo = max(1LL, K-N);
    ll hi = min(N, K-1);
    
    if (lo > hi) cout << "0\n" << '\n';
    else cout << (hi-lo+1)/2 << '\n';

}
};
