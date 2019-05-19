#include "../l/lib.h"

class DRotationSort {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B; cin >> N >> A >> B;
        vector<int> P(N); cin >> P;
        for (int &p: P) --p;
        vector<int> I(N);
        for (int i = 0; i < N; ++i) I[P[i]] = i;
//
//        vector2<int> F(N, N+1, 0); // F[i][j] => i is right of j
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                if (I[i] > I[j]) {
//                    F[i][j+1] = 1;
//                }
//            }
//            for (int j = 0; j < N; ++j) {
//                F[i][j+1] += F[i][j];
//            }
//        }

        vector2<ll> D(N+1, N+1, 1e18);
        D[0][0] = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (I[j] < i) {
                    // it is already on the left
                    D[i][j+1] = min(D[i][j+1], D[i][j]);
                } else if (P[i] == j) {
                    // it's here, that's cheap
                    D[i+1][j+1] = min(D[i+1][j+1], D[i][j]);
                } else if (P[i] > j) {
                    D[i][j+1] = min(D[i][j+1], D[i][j] + B);
                    D[i+1][j] = min(D[i+1][j], D[i][j] + A);
                } else {
                    D[i+1][j] = min(D[i+1][j], D[i][j]);
                }
            }
        }


        ll ans = 1e18;
        for (int i = 0; i <= N; ++i) {
            ans = min(ans, D[i][N]);
            ans = min(ans, D[N][i]);
        }
        cout << ans << endl;
    }
};
