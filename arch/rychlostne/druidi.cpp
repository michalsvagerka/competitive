#include "../../l/lib.h"
// #include "../l/mod.h"

class druidi {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        M += N;
        int g = 1;
        int ans = 0;
        for (int i = M; i < N*M; i+=M) {
            while (g*N < i) ++g;
            ans += min(g*N-i, i-(g-1)*N);
        }
        cout << fixed << setprecision(7) << 10000.0*ans/N/M << endl;
    }
};
