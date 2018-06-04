#include "../../../l/lib.h"
 #include "../../../l/mod.h"

constexpr int MAXN = 2001;

class gregandcaves {
public:
    void solve(istream& cin, ostream& cout) {
        vector2<FieldMod> D(MAXN, MAXN, 0);
        for (int i = 2; i < MAXN; ++i) D[1][i] = 1;
        for (int i = 2; i < MAXN; ++i) {
            vector<FieldMod> E = D[i-1];
            for (int j = 2; j < MAXN; ++j) E[j] += E[j-1];
            for (int j = 2; j < MAXN; ++j) D[i][j] += E[j] += E[j-1];
        }

        vector2<FieldMod> E = D;
        for (int i = 2; i < MAXN; ++i) {
            for (int j = 2; j < MAXN; ++j) E[i][j] -= D[i-1][j];
            for (int j = 2; j < MAXN; ++j) E[i][j] += E[i-1][j];
        }

        for (int i = 2; i < MAXN; ++i) {
            for (int j = 2; j < MAXN; ++j) D[i][j] += D[i-1][j];
        }

        int M, N; cin >> N >> M;

        FieldMod ans = 0;
        for (int w = 2; w <= M; ++w) {
            for (int m = 0; m < N; ++m) {
                ans += E[m+1][w] * D[N-m][w] * (M-w+1);
            }
        }
        cout << ans << endl;
    }
};
