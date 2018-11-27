#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, M;
    cin >> N >> M;
    vector<ll> C(M, N/M);
    for (int i = 1; i <= N%M; ++i) C[i]++;
    ll ans = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if ((i*i + j*j)%M == 0) {
                ans += C[i]*C[j];
            }
        }
    }
    cout << ans << '\n';
}
};
