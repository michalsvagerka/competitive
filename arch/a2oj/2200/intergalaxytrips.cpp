#include "../../../l/lib.h"
// #include "../l/mod.h"

class intergalaxytrips {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

//        N = 1000;


        vector2<int> W(N,N,0);
        cin >> W;
        vector2<long double> Z(N,N,0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                Z[i][j] = W[i][j]/100.0;
            }
        }
//        for (int i = 0; i < N; ++i) Z[i][i] = 1;
//        for (int i = 0; i < N-1; ++i) Z[i][i+1] = 0.01;



        vector<long double> P(N, 1e10), A(N, 0), B(N, 1);
        P[N-1] = 0;
        for (int i = 0; i < N-1; ++i) B[i] = 1 - Z[i][N-1];
        while (P[0] > 1e9) {
            pair<long double, int> Q(1e20, -1);
            for (int i = 0; i < N; ++i) {
                if (P[i] > 1e9 && B[i] < 1-1e-9) {
                    Q = min(Q, {(1 + A[i]) / (1 - B[i]), i});
                }
            }
            int j = Q.y;
            if (j != -1) {
                P[j] = Q.x;
                for (int i = 0; i < N; ++i) {
                    if (P[i] > 1e9) {
                        A[i] += B[i] * P[j] * Z[i][j];
                        B[i] *= 1 - Z[i][j];
                        if (B[i] < 1e-10) { B[i] = 0; }
                    }
                }
            }
        }

        cout << fixed << setprecision(15) << P[0] << endl;
    }
};
