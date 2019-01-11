#include "../l/lib.h"
#include <numeric>
#include "../l/mod.h"
#include "../l/fft.h"
#include "../l/fenwick.h"
#include "../l/random.h"

typedef Field<998244353> FF;

class EBeautifulMatrix {
public:
    vector<vector<FF>> Y;
    FF calc(const vector<int> &S, vector<int> &T) {
        int N = S.size();
        Fenwick<int> F(N, 0), G(N, 0), H(N, 0);

        vector<int> Inv(N);
        for (int i = 0; i < N; ++i) {
            Inv[T[i]] = i;
            F.add(i, 1);
            G.add(i, 1);
        }

        FF ans = 0;
        for (int i = 0; i < N; ++i) {
            int s = F.range(i+1, N);
            ans += H.sum(S[i]) * Y[N-1-i][s];
            ans += (G.sum(S[i])-(T[i] < S[i])*(F.get(i))) * Y[N-1-i][s-1];

            F.add(Inv[S[i]], -1);

            H.set(S[i], 0);
            G.set(S[i], 0);

            int c = G.get(T[i]);
            G.add(T[i], -c);
            H.add(T[i], c);
        }

        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

        auto F = FF::fact(N+1);
        auto I = FF::invfact(N+1);
        vector<FF> Der(N+1);
        Der[0] = 1;
        Der[1] = 0;
        Der[2] = 1;
        for (int n = 3; n <= N; ++n) Der[n] = (n-1)*(Der[n-1]+Der[n-2]);

        Y = vector2<FF>(N+1, N+1, 0);
        vector<FF> IF(2*N+1, 0);
        for (int i = 0; i <= N; ++i) IF[i] = I[i];
        FFT<998244353> fft;
        fft.fft(IF);

        for (int j = 0; j <= N; ++j) {
            vector<FF> A(2*N+1);
            for (int i = j; i <= N; ++i) A[i] = Der[i] * I[i-j];
            fft.fft(A);
            for (int i = 0; i < A.size(); ++i) A[i] *= IF[i];
            fft.fft(A, true);
            for (int i = j; i <= N; ++i) Y[i][j] = A[i] * F[i-j];
        }

        vector2<int> A(N,N);
        cin >> A;
        for (auto &AA:A) for (auto&a:AA) --a;

        Fenwick<int> Fen(N+1, 0);
        for (int i = 0; i < N; ++i) Fen.add(i, 1);
        FF ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += (Fen.sum(A[0][i]+1)-1) * F[N-1-i];
            Fen.add(A[0][i], -1);
        }

        for (int i = 1; i < N; ++i) {
            ans *= Der[N];
            ans += calc(A[i], A[i-1]);
        }

        cout << ans << endl;
    }
};
