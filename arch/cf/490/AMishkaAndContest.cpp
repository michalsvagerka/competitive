#include "../../../l/lib.h"

class AMishkaAndContest {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        int l = 0, r = N-1;
        while (l < N && A[l] <= K) ++l;
        while (r >= 0 && A[r] <= K) --r;
        if (l == N) cout << N << '\n';
        else cout << N - (r-l+1) << '\n';
    }
};
