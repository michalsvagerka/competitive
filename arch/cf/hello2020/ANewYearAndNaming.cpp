#include "../l/lib.h"

class ANewYearAndNaming {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<string> S(N), T(M); cin >> S >> T;
        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int x; cin >> x;
            --x;
            cout << S[x%N] << T[x%M] << '\n';
        }
    }
};
