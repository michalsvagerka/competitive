#include "../l/lib.h"
// #include "../l/mod.h"

class TaskF {
public:
void solve(istream& cin, ostream& cout) {
    ui N, A, B, C, D;
    cin >> N >> A >> B >> C >> D;
    constexpr int T = 30;

    constexpr int M = 300000000;
    constexpr int R = (M+T-1)/T;
    int primes = 0;
    vector<int> W(T, -1);
    int c = 0;
    for (int i = 0; i < T; ++i) {
        if (i%2 && i%3 && i%5) {
            W[i] = c++;
        }
    }
    bitset<80000000> Z;
    Z.set();

    ui ans = 0;
    auto upd = [&](ui p) {
        ui w = 0;
        for (ll r = p; r < M; r*=p) w += N/r;
        ans += (A*p*p*p + B*p*p + C*p + D)*w;
    };
    upd(2); upd(3); upd(5);

    for (int p: {7,11,13,17,19,23,29}) {
        upd(p);
        for (ll q = p*p; q < M; q+=p+p) {
            if (q >= T && W[q%T] != -1) {
                Z[((q/T)<<3) + W[q%T]] = false;
            }
        }
    }

    for (int p = T+1; p < M; p+=2) {
        if (W[p%T] != -1 && Z[((p/T)<<3) + W[p%T]]) {
            upd(p);
            if (p < 18000) {
                for (int q = p * p; q < M; q += p + p) {
                    if (W[q % T] != -1) {
                        Z[((q / T) << 3) + W[q % T]] = false;
                    }
                }
            }
        }
    }

    cout << ans << endl;
}
};
