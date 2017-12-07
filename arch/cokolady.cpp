#include "../l/lib.h"
// #include "../l/mod.h"

class cokolady {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, K; cin >> N >> K;
            bool rev = K > N/2;
            vector<double> P(N); cin >> P;
            if (rev) {
                for(double&p:P) p = 1-p;
                K = N - K + 1;
            }

            vector<double> D(K+1,0.0);
            D[0] = 1.0;
            for (int i = 0; i < N; ++i) {
                vector<double> E(K+1,0.0);
                E[K] = D[K];
                for (int j = min(i,K-1); j >= 0; --j) {
                    E[j+1] += D[j] * P[i];
                    E[j] += D[j] * (1-P[i]);
                }
                swap(E,D);
            }

            double ans = D[K];
            if (rev) ans = 1-ans;
            cout << fixed << setprecision(4) << ans << '\n';
        }

    }
};
