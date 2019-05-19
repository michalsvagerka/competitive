#include "../l/lib.h"
// #include "../l/mod.h"

class AParity {
public:
void solve(istream& cin, ostream& cout) {
    int B, K; cin >> B >> K;
    B %= 2;
    vector<int> A(K); cin >> A;
    int tot = A[K-1];
    for (int i = 0; i < K-1; ++i) {
        tot += B * A[i];
    }
    cout << (tot%2==0?"even":"odd") << '\n';
}
};
