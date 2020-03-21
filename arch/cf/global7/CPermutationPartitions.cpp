#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;
class CPermutationPartitions {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> P(N); cin >> P;
        FF a = 1, b = 0;
        for (int i = 0; i < N; ++i) {
            if (P[i] > N-K) {
                b = a;
            } else {
                a = a + b;
            }
        }
        cout << ll(N + N-K+1)*ll(K)/2 << ' ' << b << '\n';
    }
};
