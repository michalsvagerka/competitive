#include "../../../l/lib.h"
// #include "../l/mod.h"

class watching_movie {
public:
    void solve(istream& cin, ostream& cout) {
        int N, X; cin >> N >> X;
        int ans = 0;
        int last = 1;
        for (int i = 0; i < N; ++i) {
            int l, r; cin >> l >> r;
            ans += (l-last)%X;
            ans += r-l+1;
            last = r+1;
        }
        cout << ans << '\n';
    }
};
