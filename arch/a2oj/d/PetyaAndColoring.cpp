#include "../l/lib.h"
 #include "../l/mod.h"

class PetyaAndColoring {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> M >> K;
    if (M == 1) {
        cout << FieldMod{K}.pow(N) << '\n';
        return;
    }


    vector2<FieldMod> C(N+1, N+1, 0);
    C[0][0] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            C[i+1][j] += C[i][j] * j;
            C[i+1][j+1] += C[i][j];
        }
    }

    auto F = FieldMod::fact(1000000);
    auto I = FieldMod::invfact(1000000);

    FieldMod ans = 0;
    for (int a = 1; a <= N; ++a) {
        FieldMod m = C[N][a] * C[N][a] * F[a] * F[a] * F[K];
        for (int c = 0; c <= a; ++c) {
            int s = a - c;
            if (s + s + c > K) continue;
            ans += m * I[a-c] * I[a-c] * I[K - a - a + c] * I[c] * FieldMod{c}.pow(N*(M-2));
        }
    }

    cout << ans << endl;
}
};
