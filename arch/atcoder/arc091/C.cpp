#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        if (N > M) swap(N,M);
        if (M == 1) cout << "1\n";
        else if (N == 1) cout << M-2 << '\n';
        else cout << ll(N-2)*ll(M-2) << '\n';
    }
};
