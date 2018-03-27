#include <numeric>
#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N), B(M);
        cin >> A >> B;
        int m = *max_element(A.begin(),A.end());
        int n = *max_element(B.begin(),B.end());
        int s = accumulate(A.begin(), A.end(), 0) + *max_element(A.begin(),A.end()) * (M-1);
        int t = 0;

        int i = 0, j = N-1;
        while (A[i] < m) ++i;
        while (A[j] < m) --j;

        t = accumulate(B.begin(), B.end(), 0) + i * B[0] + (N-1-j) * B[M-1] + (j-i) * n;
        cout << 1000000000LL * s + t << endl;
    }
};
