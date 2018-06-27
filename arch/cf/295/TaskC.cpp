#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    string S; cin >> S;

    auto F = FieldMod::fact(N);
    auto I = FieldMod::invfact(N);
    vector<FieldMod> W(N+1, 1);
    for (int i = 0; i < N; ++i) W[i+1] = W[i] * 10;

    auto choose = [&](int n, int k) {
        if (k < 0 || k > n) return FieldMod{0};
        else return F[n] * I[n-k] * I[k];
    };

    vector<FieldMod> Z(N+1, 0);
    for (int i = 0; i < N; ++i) {
        Z[i+1] = Z[i] + W[i] * choose(N-i-2, K-1);
    }

    FieldMod ans = 0;
    for (int i = 0; i < N; ++i) {
        int a = N-1-i;
        ans += (Z[i] + W[i] * choose(a, K)) * (S[a]-'0');
    }

    cout << ans << '\n';
}
};
