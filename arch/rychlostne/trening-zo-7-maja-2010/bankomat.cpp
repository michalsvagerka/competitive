#include "../l/lib.h"
// #include "../l/mod.h"

class bankomat {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int C, N; cin >> C >> N; ++C;
            vector<int> P(C,0);
            P[0] = 1;
            for (int i = 0; i < N; ++i) {
                int p,k; cin >> p >> k;
                if (p == 0) continue;
                vector<int> R = P;
                for (int c = 0; c + k < C; ++c) R[c+k] += R[c];
                k *= p+1;
                for (int c = 0; c < C; ++c) P[c] = R[c] != (c-k >= 0?R[c-k]:0);
            }

            for (int c = C-1; c >= 0; --c) {
                if (P[c]) { cout << c << endl; break; }
            }
        }
    }
};
