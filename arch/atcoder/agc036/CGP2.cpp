#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class CGP2 {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        auto F = FF::fact(N+2*M);
        auto I = FF::invfact(N+2*M);

        FF ans = 0;
        for (int i = 0; i <= M/2; ++i) {
            int j = M-2*i;
            if (j > N) continue;

            FF tot = F[(M+i) + N - 1] * I[M+i];
            FF oneHasM = F[i + N - 2] * I[i] * (N-1);
            FF oneHasMoreThanM = i == 0 ? 0 : F[i + N - 2] * I[i-1];
            FF allHaveLessThanM = tot - oneHasM * N - oneHasMoreThanM * N;

            FF cur = allHaveLessThanM + oneHasM * (N-j);
            ans += cur * I[j] * I[N-j];
        }
        cout << ans * N << endl;
    }
};
