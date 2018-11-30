#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FFT;

auto F = FFT::fact(3e5);
auto I = FFT::invfact(3e5);

class BRGBColoring {
public:
    void solve(istream& cin, ostream& cout) {
        ll N, A, B; cin >> N >> A >> B;
        ll K; cin >> K;
        FFT ans = 0;
        for (int i = 0; i <= N; ++i) {
            ll b = (K-i*A)/B;
            if ((K - i * A) % B == 0 && b >= 0 && b <= N) {
                ans += I[i] * I[N-i] * I[b] * I[N-b];
            }
        }
        cout << ans * F[N] * F[N] << endl;
    }
};
