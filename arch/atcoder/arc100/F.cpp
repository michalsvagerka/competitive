#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class F {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> K >> M;

    vector<int> A(M); cin >> A;
    vector<int> U(K, false);
    int pref = 0;
    for (pref = 0; pref < min(K,M); ++pref) {
        if (U[A[pref]-1]) break;
        U[A[pref]-1] = true;
    }

    fill(U.begin(), U.end(), false);
    int suf = 0;
    for (suf = 0; suf < min(K,M); ++suf) {
        if (U[A[M-suf-1]-1]) break;
        U[A[M-suf-1]-1] = true;
    }

    bool contains = false;
    for (int i = 0; i < M-K+1; ++i) {
        fill(U.begin(), U.end(), false);
        for (int j = 0; j < K; ++j) {
            U[A[i+j]-1] = true;
        }
        if (count(U.begin(),U.end(),false) == 0) {
            contains = true;
            break;
        }
    }

    auto F = FieldMod::fact(N);
    auto I = FieldMod::invfact(N);

    if (contains) {
        cout << FieldMod{K}.pow(N-M) * (N-M+1) << endl;
        return;
    }

    FieldMod ans = 0;
    if (suf == M) {
        for (int left = 0; left + suf <= K; ++left) {
            // totally on the right
            ans += F[K-M] * FieldMod{K}.pow(N-K);
            ans += F[K-M] * FieldMod{K-1} * (N-K) * FieldMod{K}.pow(N-K-1);
        }
    }

    vector2<FieldMod> C(2, N+1), E(2, N+1);
    vector<int> W{suf, pref};
    for (int w = 0; w < 2; ++w) {
        vector2<FieldMod> D(N + 1, K + 1, 0);
        D[0][W[w]] += 1;
        for (int i = 0; i < N; ++i) {
            // permutation already done
            D[i + 1][K] += D[i][K] * K;

            // add character not in permutation
            for (int k = 1; k < K; ++k) {
                D[i + 1][k + 1] += D[i][k] * (K - k);
            }

            // add character in permutation
            FieldMod z = 0;
            for (int k = K - 1; k >= 1; --k) {
                z += D[i][k];
                D[i + 1][k] += z;
            }
        }

        for (int i = 0; i <= N; ++i) {
            C[w][i] = D[i][K];
            E[w][i] = 0;
            for (int j = 0; j < K; ++j) {
                E[w][i] += D[i][j];
            }
        }
    }

    for (int pos = 0; pos <= N-M; ++pos) {
        int left = pos;
        int right = N-pos-M;
        ans += C[0][left] * E[1][right] + E[0][left] * C[1][right] + C[0][left] * C[1][right];
    }
    cout << ans << endl;

}
};
