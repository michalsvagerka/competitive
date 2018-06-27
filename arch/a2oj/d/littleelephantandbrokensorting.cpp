#include "../../../l/lib.h"
// #include "../l/mod.h"

class littleelephantandbrokensorting {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        vector2<double> D(N,N,0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                D[i][j] = A[i] > A[j];
            }
        }

        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b; --a; --b;
            for (int j = 0; j < N; ++j) {
                if (j != a && j != b) {
                    D[j][a] = D[j][b] = (D[j][a] + D[j][b]) / 2;
                    D[a][j] = D[b][j] = (D[b][j] + D[a][j]) / 2;
                }
            }
            D[a][b] = D[b][a] = (D[a][b] + D[b][a]) / 2;
        }


        double ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                ans += D[i][j];
            }
        }
        cout << fixed << setprecision(10) << ans << endl;
    }
};
