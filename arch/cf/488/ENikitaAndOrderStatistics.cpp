#include "../../../l/lib.h"
#include "../../../l/fft.h"
#include "../../../l/crt.h"

class ENikitaAndOrderStatistics {
public:
    template <ui N> vector<Field<N>> solve(const vector<int> &C) {
        int M = C.size();
        FFT<N> F;
        vector<Field<N>> A(2*M, 0), B(2*M, 0);
        for (int i = 0; i < M; ++i) {
            A[i] = C[i];
            B[M-1-i] = C[i];
        }

        F.fft(A);
        F.fft(B);
        for (int i = 0; i < A.size(); ++i) A[i] *= B[i];
        F.fft(A, true);
//        A[M] -= 2*M;
        return A;


        // M-1-i    + j  = j-i + (M-1)
    }

    void solve(istream& cin, ostream& cout) {
        int N, X; cin >> N >> X;
        vector<int> A(N); cin >> A;
        vector<int> C(N+1, 0);
        int c = 0;
        C[c]++;
        vector<ll> Ans(N+1, 0);
        int f = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] >= X) {
                f++;
                Ans[0] += f;
            } else { f = 0; }
            c += A[i] < X;
            C[c]++;
        }

        auto D = solve<998244353u>(C);
        auto E = solve<924844033u>(C);
        Chinese CH({998244353u,924844033u}, 998244353LL*924844033LL);

        for (int i = 0; i < N; ++i) {
            Ans[i+1] = CH({(ui)D[N+i+1], (ui)E[N+i+1]});
        }
        cout << Ans;

    }
};
