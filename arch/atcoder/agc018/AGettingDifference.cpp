#include "../l/lib.h"
// #include "../l/mod.h"

class AGettingDifference {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        int g = A[0];
        for (int j = 1; j < N; ++j) g = gcd(g, A[j]);
        if (K % g != 0 || K > A.back()) cout << "IMPOSSIBLE\n";
        else cout << "POSSIBLE\n";
    }
};
