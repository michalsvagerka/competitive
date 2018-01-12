#include "../l/lib.h"
// #include "../l/mod.h"

class mikrozdaj {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int P,N; cin >> P >> N;
            vector<int> A(N); cin >> A;
            int ans = bsl(1, P, [&](int x) {
                int t = 0;
                for (auto a:A) t += min(a,x);
                return t >= P;
            });
            if (ans == -1) {
                cout << "Boli ste zli, nic nedostanete!\n";
            } else {
                cout << ans << '\n';
            }
        }
    }
};
