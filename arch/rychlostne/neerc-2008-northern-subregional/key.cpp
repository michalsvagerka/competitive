#include "../l/lib.h"
// #include "../l/mod.h"

class key {
public:
    void solve(istream& cin, ostream& cout) {
        ui N, M; cin >> N >> M;
        vector<ll> A(N); cin >> A;
        sort(A.begin(),A.end());
        vector<ll> B(M);
        ll T = 0; ui j = 0;
        for (ui i = 0; i < M; ++i) {
            while (j < N && A[j] <= T+1) T += A[j++];
            B[i] = T+1;
            T += T + 1;
        }
        cout << B;
    }
};
