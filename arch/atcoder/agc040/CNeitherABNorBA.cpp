#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class CNeitherABNorBA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        auto F = FF::fact(N);
        auto I = FF::invfact(N);

        vector<FF> P(N+1, 1);
        for (int i = 1; i <= N; ++i) {
            P[i] = P[i-1] * 2;
        }
        FF ans = FF{3}.pow(N);
        for (int i = N/2+1; i <= N; ++i) {
            ans -= 2 * F[N] * I[i] * I[N-i] * P[N-i];
        }

        cout << ans << '\n';
    }
};
