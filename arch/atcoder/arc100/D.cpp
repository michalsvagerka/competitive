#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector<ll> S(N+1, 0);
    for (int i = 0; i < N; ++i) {
        S[i+1] = S[i] + A[i];
    }

    ll ans = 1e18;
    for (int c = 2; c <= N-2; ++c) {
        int b = bsh(1, c-1, [&](int z) { return S[z] <= S[c] - S[z]; });
        if (b == -1) b = 1;

        int d = bsh(c+1, N-1, [&](int z) { return S[z] - S[c] <= S[N] - S[z]; });
        if (d == -1) d = c+1;

        for (int db = 0; db <= 1; ++db) {
            for (int dd = 0; dd <= 1; ++dd) {
                if (b + db != c && d + dd != N) {
                    vector<ll> W{S[b+db], S[c]-S[b+db], S[d+dd]-S[c], S[N]-S[d+dd]};
                    ll lo = *min_element(W.begin(),W.end());
                    ll hi = *max_element(W.begin(),W.end());
                    ans = min(ans, hi-lo);
                }
            }
        }
    }

    cout << ans << endl;


}
};
