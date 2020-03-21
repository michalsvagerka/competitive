#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/fft.h"

typedef Field<998244353> FF;

class D1WrongAnswerOnTest233EasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> H(N); cin >> H;
        int M = 0;
        for (int i = 0; i < N; ++i) {
            int a = H[i];
            int b = H[(i+1)%N];
            if (a != b) {
                M++;
            }
        }


        if (M == 0) {
            cout << 0 << '\n';
            return;
        }

        auto F = FF::fact(M+2);
        auto I = FF::invfact(M+2);

        auto J = I;
        while (J.size() < 3*I.size()) J.push_back(0);
        FFT<998244353> fft;
        fft.fft(J);
        for (int i = 0; i < J.size(); ++i) J[i] *= J[i];
        fft.fft(J, true);

        FF ans = 0;
        for (int s = 0; s <= M; ++s) {
            FF r = J[s];
            if (s%2 == 0) r -= I[s/2] * I[s/2];
            if (K == 2 && s != M) {
                continue;
            }
//            cout << s << ' ' << r << ' ' << F[M-s] << ' ' << FF{(K-2)%998244353}.pow(M-s) << endl;
            ans += r * I[M-s] * FF{(K-2)%998244353}.pow(M-s);
        }

        ans /= 2;
        ans *= F[M];
        ans *= FF{K%998244353}.pow(N-M);
        cout << ans << '\n';
    }
};
