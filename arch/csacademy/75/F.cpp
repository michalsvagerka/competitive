#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/fft.h"

typedef Field<998244353> FF;

class F {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        auto fct = FF::fact(N);
        auto inv = FF::invfact(N);

        FFT<998244353> ntt;
        // choose P_y >= y:
        // then floor((P_y-1)/2) * (P_y-2 choose y-2) * F[y-2] * F[N-P_y]

        vector<FF> Z(2*N+1, 0), R(2*N+1);
        for (int i = 1; i <= N; ++i) {
            Z[N-i] = ((i-1)/2) * fct[i-2];
            R[i-1] = inv[i-1];
        }

        ntt.fft(Z);
        ntt.fft(R);
        for (int i = 0; i <= Z.size(); ++i) Z[i] *= R[i];
        ntt.fft(Z, true);

        for (int q = 0; q < Q; ++q) {
            int x,y; cin >> x >> y;
            FF ans = Z[N-y];
//            for (int py = y; py <= N; ++py) {
//                ans += Z[N-py] * R[py-y];
//            }
            cout << ans * fct[N-y] << '\n';
        }
    }
};
