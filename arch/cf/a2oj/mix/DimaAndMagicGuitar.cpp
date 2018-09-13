#include "../l/lib.h"
// #include "../l/mod.h"

class DimaAndMagicGuitar {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, K, S;
    cin >> N >> M >> K >> S;
    vector2<int> A(N, M); cin >> A;
    for (auto&a:A) for (auto&aa:a) --aa;
    vector<int> Q(S); cin >> Q;
    for (auto&q:Q) --q;
    vector2<bool> D(K, K, false);
    for (int i = 1; i < S; ++i) {
        D[Q[i]][Q[i-1]] = true;
        D[Q[i-1]][Q[i]] = true;
    }

    vector2<int> LO(N, K, M), HI(N, K, -1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            LO[i][A[i][j]] = min(LO[i][A[i][j]],j);
            HI[i][A[i][j]] = j;
        }
    }

    int best = 0;
    for (int k = 0; k < K; ++k) {
        for (int l = k; l < K; ++l) {
            if (!D[k][l]) continue;
            for (int i = 0; i < N; ++i) {
                if (LO[i][k] == M) continue;
                for (int j = N-1; j >= i; --j) {
                    if (LO[j][l] == M) continue;
                    best = max(best, j-i + abs(LO[j][l]-LO[i][k]));
                    best = max(best, j-i + abs(LO[j][l]-HI[i][k]));
                    best = max(best, j-i + abs(HI[j][l]-LO[i][k]));
                    best = max(best, j-i + abs(HI[j][l]-HI[i][k]));

                    if (j-i+M-1 <= best) break;
                }
                for (int j = 0; j < i; ++j) {
                    if (LO[j][l] == M) continue;
                    best = max(best, i-j + abs(LO[j][l]-LO[i][k]));
                    best = max(best, i-j + abs(LO[j][l]-HI[i][k]));
                    best = max(best, i-j + abs(HI[j][l]-LO[i][k]));
                    best = max(best, i-j + abs(HI[j][l]-HI[i][k]));

                    if (i-j+M-1 <= best) break;
                }
            }
        }
    }
    cout << best << endl;
}
};
