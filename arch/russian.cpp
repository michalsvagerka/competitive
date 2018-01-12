#include "../l/lib.h"
// #include "../l/mod.h"

class russian {
public:
    void solve(istream& cin, ostream& cout) {
        int N,K; cin >> N >> K;
        if (N > 6) { cout << "@\n"; return; }

        ll den = 1;
        for (int i = 0; i < K; ++i) den *= 6;
        vector<ll> W(N,den/N);
        for (int i = 0; i < K; ++i) {
            den /= 6;
            for (int j = 0; j < N; ++j) {
                if (W[j] >= den) {
                    W[j] -= den;
                    if (i == K-1) cout << char('A'+j) << endl;
                    break;
                }
            }
        }
    }
};
