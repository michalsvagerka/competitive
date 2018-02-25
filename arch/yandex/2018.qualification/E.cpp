#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<string> W(N);
        cin >> W;

        unordered_map<string, int> M;
        for (int i = 0; i < K; ++i) {
            string S; cin >> S;
            M[S] = i+1;
        }

        vector<int> R(N), C(K+1, 0);
        for (int i = 0; i < N; ++i) {
            R[i] = M[W[i]];
        }

        int e = 0, f = 0; C[0] = 1;
        ll ans = 0;
        for (int b = 0; b < N; ++b) {
            while (e < N && f < K) if (!C[R[e++]]++) ++f;
            if (f == K) ans += N - e + 1;
            if (!--C[R[b]]) --f;
        }

        cout << ans << '\n';
    }
};
