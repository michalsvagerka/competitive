#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<998244353> F;
class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<F> T(N+1, 1), L(N+1, 0);
    F N3 = F{3}.pow(N);
    F N33 = N3-3;
    F ans = N3.pow(N) - N33.pow(N);

    auto FF = F::fact(N);
    auto II = F::invfact(N);

    for (int i = 1; i <= N; ++i) {
        F x = 0;
        x += 3 * (F{3}.pow(N - i) - 1).pow(N);
        x += (F{3}.pow(i) - 3) * (F{3}.pow(N-i)).pow(N);

        x *= FF[N] * II[N-i] * II[i];
        if (i%2) {
            ans += x;
        } else {
            ans -= x;
        }

    }
    cout << ans << '\n';
}
};
