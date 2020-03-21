#include "../l/lib.h"

class BAlyonaAndFlowers {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        int ans = 0;
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            int tot = 0;
            for (int j = a; j <= b; ++j) {
                tot += A[j];
            }
            ans += max(0, tot);
        }
        cout << ans << '\n';
    }
};
