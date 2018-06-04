#include "../../../l/lib.h"
// #include "../l/mod.h"

class jeffinversions {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N); cin >> P;
        for (int&p:P) if (p<0) p = -p;

        ll ans = 0;
        vector<int> S(N), T(N);
        for (int i = 0; i < N; ++i) {
            int s = 0, t = 0;
            for (int j = 0; j < i; ++j) {
                if (P[j] < P[i]) s++;
            }
            for (int j = i+1; j < N; ++j) {
                if (P[j] < P[i]) t++;
            }
            ans += min(s,t);
        }

        cout << ans << '\n';
    }
};
