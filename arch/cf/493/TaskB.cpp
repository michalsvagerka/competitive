#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    ll ans = 0;

    for (int fives = 0; fives < 9; ++fives) {
        for (int tens = 0; tens < 9; ++tens) {
            if (fives + tens > N) continue;
            bool fail = false;
            for (int i = 0; i <= fives; ++i) {
                for (int j = 0; j <= tens; ++j) {
                    fail |= ((4*i + 9*j)%49 == 0) && (i+j > 0);
                }
            }
            if (!fail) {
                ans += (N - fives - tens + 1);
            }
        }
    }
    cout << ans << endl;

}
};
