#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/fft.h"

typedef Field<924844033u> FF;
auto F = FF::fact(400000);
auto I = FF::invfact(400000);

class FManyEasyProblems {
public:
    vector<vector<int>> E;
    vector<FF> S;

    int size(int u, int p) {
        int s = 1;
        for (int v : E[u]) {
            if (v != p) {
                s += size(v, u);
            }
        }
        S[s]++;
        return s;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        S.assign(N+1, 0);

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        size(0, -1);
        S[N]--;

        FFT<924844033u> fft;
        vector<FF> R(3*N, 0), T(3*N, 0);
        for (int i = 0; i <= N; ++i) {
            R[i] = I[N-i];
            T[i] = (S[i]+S[N-i]) * F[i];
        }
        fft.fft(R);
        fft.fft(T);
        for (int i = 0; i < R.size(); ++i) R[i] *= T[i];
        fft.fft(R, true);

        for (int k = 1; k <= N; ++k) {
            cout << F[N] * I[k] * I[N-k] * N - R[N+k] * I[k] << '\n';
        }
    }
};
