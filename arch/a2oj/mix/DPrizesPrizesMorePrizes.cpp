#include "../l/lib.h"
// #include "../l/mod.h"

class DPrizesPrizesMorePrizes {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> P(N); cin >> P;
    vector<int> A(5); cin >> A;
    vector<ll> C(5, 0);
    ll T = 0;
    for (int p: P) {
        T += p;
        for (int i = 4; i >= 0; --i) {
            if (T >= A[i]) {
                C[i] += T / A[i];
                T %= A[i];
            }
        }
    }
    
    cout << C << T << endl;
}
};
