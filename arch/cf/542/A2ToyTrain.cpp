#include "../l/lib.h"

class A2ToyTrain {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> A(M); cin >> A;
        vector<int> C(N, 0), D(N, N);
        for (pii a: A) {
            --a.x; --a.y;
            C[a.x]++;
            D[a.x] = min(D[a.x], (N + a.y - a.x) % N);
        }

        vector<int> Ans(N, 0);
        for (int i = 0; i < N; ++i) {
            int ans = 0;
            for (int j = 0; j < N; ++j) {
                if (C[j]) ans = max(ans, (C[j]-1)*N + D[j] + (j-i+N)%N);
            }
            Ans[i] = ans;
        }
        cout << Ans;
    }
};
