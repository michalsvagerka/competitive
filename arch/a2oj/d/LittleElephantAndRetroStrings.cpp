#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/fenwick.h"

class LittleElephantAndRetroStrings {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    string S; cin >> S;
    vector2<FieldMod> D(2, N-K+1, 0);
    vector<FieldMod> X(N+1, 1), R(N+1, 1);
    vector<int> W(N+1,0);
    FieldMod half = FieldMod{1}/2;
    for (int r = 0; r < 2; ++r) {
        char z = r ? 'B' : 'W';
        for (int i = 0; i < N; ++i) {
            W[i+1] = W[i] + (S[i] == z);
            X[i+1] = X[i];
            R[i+1] = R[i];
            if (S[i] == 'X') {
                X[i+1] += X[i];
                R[i+1] *= half;
            }
        }

        Fenwick<FieldMod> F(N, 0), G(N, 0);
        FieldMod f = 0, g = 0;
        for (int i = 0; i+K <= N; ++i) {
            if (W[i + K] == W[i]) {
                D[r][i] = X[i] - f - X[i] * g;
            }
            if (i-K>=0) {
                f -= D[r][i-K];
                g += D[r][i-K] * R[i];
            }
            f += D[r][i];
        }


        for (int i = 0; i+K <= N; ++i) D[r][i] *= R[i+K];
        if (r) for (int i = 1; i+K <= N; ++i) D[1][i] += D[1][i-1];
        else reverse(S.begin(),S.end());
    }

    FieldMod ans = 0;
    for (int i = 0; i <= N-2*K; ++i) {
        ans += D[0][i] * D[1][N - 2 * K - i];
    }
    cout << ans * X[N] << endl;
}
};
