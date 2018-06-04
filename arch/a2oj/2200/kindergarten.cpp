#include "../../../l/lib.h"
// #include "../l/mod.h"

class kindergarten {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) {
            cout << "0\n";
            return;
        }

        vector<int> A(N); cin >> A;
        vector<ll> D(N-1);
        for (int i = 0; i < N-1; ++i) D[i] = A[i+1] - A[i];
        vector2<ll> S(N-1, 2, 0);
        S[0][1] = abs(D[0]);
        for (int i = 1; i < N-1; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (j && k && (D[i] > 0) != (D[i-1] > 0)) continue;
                    S[i][k] = max(S[i][k], S[i-1][j] + k*abs(D[i]));
                }
            }
        }

        cout << max(S[N-2][0], S[N-2][1]) << '\n';
    }
};
