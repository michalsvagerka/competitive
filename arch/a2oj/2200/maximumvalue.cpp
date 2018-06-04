#include "../l/lib.h"
// #include "../l/mod.h"

constexpr int mx = 1e6;
class maximumvalue {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> P(2*mx+1, 0);
        for (int a:A) P[a] = a;
        for (int i = 1; i <= 2*mx; ++i) P[i] = max(P[i], P[i-1]);
        int ans = 0;
        for (int i = 1; i <= mx; ++i) {
            if (P[i] == i) {
                for (int j = 2*i-1; j < 2*mx+1; j += i) {
                    ans = max(ans, P[j]%i);
                }
            }
        }

        cout << ans << '\n';

    }
};
