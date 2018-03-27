#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include <numeric>

typedef Field<998244353> T;

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        auto F = T::fact(N);
        auto I = T::invfact(N);
        vector<T> D(N+1, 0);
        D[0] = N%2 ? -F[N] : F[N];
        for (auto&f:F) f = f.pow(K);
        for (auto&i:I) i = i.pow(K);
        for (int j = 0; j < N; ++j) {
            for (int k = 1; k + j <= N; ++k) {
                D[j+k] -= D[j] * I[k];
            }
        }

        cout << D[N] << endl;
    }
};
