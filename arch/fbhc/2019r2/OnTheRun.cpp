#include "../l/lib.h"

class OnTheRun {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M, K; cin >> N >> M >> K;
            vector<pii> P(K+1); cin >> P;
            bool win = true;
            if (K == 2) {
                int a = (P[0].x + P[0].y) % 2;
                int b = (P[1].x + P[1].y) % 2;
                int c = (P[2].x + P[2].y) % 2;
                if (a == b && a == c) win = false;
            }

            cout << "Case #" << t+1 << ": " << "YN"[win] << '\n';
        }
    }
};
