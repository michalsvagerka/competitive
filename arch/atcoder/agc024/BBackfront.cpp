#include "../l/lib.h"
// #include "../l/mod.h"

class BBackfront {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> P(N);
        for (int i = 0; i < N; ++i) P[A[i]-1] = i;
        int ans = 1, cur = 1;
        for (int i = 1; i < N; ++i) {
            if (P[i] > P[i-1]) ++cur;
            else cur = 1;
            ans = max(ans, cur);
        }
        cout << N-ans << endl;
    }
};
