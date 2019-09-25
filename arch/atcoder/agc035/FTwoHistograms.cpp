#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/fft.h"

typedef Field<998244353> FF;

class FTwoHistograms {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;

        auto F = FF::fact(500001);
        auto I = FF::invfact(500001);
        FF ans = 0;
        vector<FF> MP(N+1, 1), NP(M+1, 1);
        for (int i = 0; i < N; ++i) MP[i+1] = MP[i] * (M+1);
        for (int i = 0; i < M; ++i) NP[i+1] = NP[i] * (N+1);

        for (int i = 0; i <= min(M,N); i+=2) {
            ans += MP[N-i] * NP[M-i] * I[i] * I[N-i] * I[M-i];
        }

        for (int i = 1; i <= min(M,N); i += 2) {
            ans -= MP[N-i] * NP[M-i] * I[i] * I[N-i] * I[M-i];
        }

        cout << ans * F[M] * F[N] << endl;
    }
};
