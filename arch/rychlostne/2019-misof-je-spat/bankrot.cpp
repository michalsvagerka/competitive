#include "../l/lib.h"

class bankrot {
public:
    void solve(istream& cin, ostream& cout) {
        int T, D, K; cin >> T >> D >> K;
        vector<vector<int>> X(D);
        for (int t = 0; t < T; ++t) {
            int S, A, B; cin >> S >> A >> B;
            --A; --B;
            if (S < 0) {
                X[A].push_back(S);
            } else {
                X[B].push_back(S);
            }
        }

        for (int i = 0; i < D; ++i) {
            sort(X[i].begin(),X[i].end());
            for (int x: X[i]) {
                K += x;
                if (K < 0) {
                    cout << "YES\n";
                    return;
                }
            }
        }

        cout << "NO\n";
    }
};
