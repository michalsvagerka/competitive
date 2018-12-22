#include "../l/lib.h"
 #include "../l/mod.h"

 typedef Field<998244353> FF;

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> M >> K;
    auto F = FF::fact(10000);
    auto I = FF::invfact(10000);

    cout << FF{M} * F[N-1] * I[K] * I[N-1-K] * FF{M-1}.pow(K) << '\n';
}
};
