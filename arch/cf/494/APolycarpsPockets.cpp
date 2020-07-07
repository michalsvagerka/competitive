#include "../../../l/lib.h"

class APolycarpsPockets {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        map<int, int> C;
        for (int i = 0; i < N; ++i) {
            int a; cin >> a; C[a]++;
        }

        int ans = 0;
        for (pii c: C) ans = max(ans, c.y);
        cout << ans << '\n';
    }
};
