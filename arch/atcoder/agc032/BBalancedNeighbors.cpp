#include "../l/lib.h"

class BBalancedNeighbors {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> E;
        if (N == 3) {
            E.push_back({1, 3});
            E.push_back({2, 3});
        } else if (N % 2 == 0) {
            for (int i = 1; i <= N; ++i) {
                for (int j = i + 1; j <= N; ++j) {
                    if (i + j != N + 1) E.push_back({i, j});
                }
            }
        } else {
            for (int i = 1; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    if (i + j != N) E.push_back({i, j});
                }
                E.push_back({i, N});
            }
        }

        cout << E.size() << '\n';
        for (pii e: E) cout << e << '\n';
    }
};
