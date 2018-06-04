#include "../../../l/lib.h"
// #include "../l/mod.h"

class towers {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), P(N+1, 0); cin >> A;
        for (int i = 0; i < N; ++i) {
            P[i+1] = P[i] + A[i];
        }

        vector2<int> D(N+1,N+1,1e9);
        for (int i = 1; i <= N; ++i) D[1][i] = P[i];
        int ans = N-1;
        for (int j = 2; j <= N; ++j) {
            for (int k = j-1; k < N; ++k) {
                if (P[N]-P[k] >= D[j-1][k]) {
                    int x = bsl(k+1, N, [&](int y) { return P[y]-P[k] >= D[j-1][k]; });
                    D[j][x] = min(D[j][x], P[x]-P[k]);
                }

                D[j][k+1] = min(D[j][k+1], D[j][k] + A[k]);
            }

            if (D[j][N] != 1e9) { ans = N-j; }
        }

        cout << ans << endl;
    }
};
