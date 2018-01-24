#include "../l/lib.h"
// #include "../l/mod.h"

class cukriky {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int K,N; cin >> K >> N;
            if (N < K) cout << N-1 << '\n';
            else if (K == 1) cout << "nekonecno\n";
            else cout << (N-1)/(K-1) * K + (N-1)%(K-1) << "\n";
        }

    }
};
