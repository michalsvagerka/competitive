#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/primes.h"

typedef Field<998244353> FF;

constexpr int MX = 1000000;

// 15-20 minutes

class CLCMs {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;

        vector<int> P(MX+1, 0);
        for (int i = 2; i <= MX; ++i) {
            if (P[i] == 0) {
                for (int j = i; j <= MX; j += i) P[j] = i;
            }
        }

        vector<FF> F(MX+1, 1);
        for (int i = 1; i <= MX; ++i) {
            for (int j = 2; i*j <= MX; ++j) {
                F[i*j] -= F[i]*j;
            }
        }

        vector<FF> S(MX+1, 0);
        for (int i = 0; i < N; ++i) S[A[i]] += A[i];

        for (int i = 1; i <= MX; ++i) {
            for (int j = i+i; j <= MX; j += i) S[i] += S[j];
        }

        FF ans = 0;
        for (int i = 1; i <= MX; ++i) ans += F[i] * S[i] * S[i] / i;
        for (int i = 0; i < N; ++i) ans -= A[i];
        ans /= 2;
        cout << ans << endl;
    }
};
