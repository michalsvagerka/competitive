#include "../l/lib.h"
// #include "../l/mod.h"

class findmax {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M,K; cin >> N >> M >> K;
        vector<int> A(N, 0);
        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b; --a; --b;
            A[a] = min(A[a], A[b]);
            A[b]++;
        }

        int ans = 0;
        for (int i = 1; i < N; ++i) {
            if (A[i] <= K) ans += 1 + K - A[i];
        }
        cout << ans << endl;
    }
};
