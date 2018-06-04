#include "../../../l/lib.h"
// #include "../l/mod.h"

class obedperm {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> S(K); cin >> S;
        vector<bool> U(N, false);
        for (int s:S) U[s-1] = true;
        int j = 0;
        for (int i = 0; i < N; ++i) {
            while (j < K && S[j] <= i) cout << S[j++] << '\n';
            if (!U[i]) cout << i+1 << '\n';
        }
        while (j < K) cout << S[j++] << '\n';

    }
};
