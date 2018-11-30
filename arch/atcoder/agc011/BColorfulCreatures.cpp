#include "../l/lib.h"
// #include "../l/mod.h"

class BColorfulCreatures {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        sort(A.begin(),A.end());
        vector<ll> P(N+1, 0);
        for (int i = 0; i < N; ++i) P[i+1] = P[i] + A[i];
        int j = N-1;
        while (j > 0 && 2*P[j] >= A[j]) --j;
        cout << N-j << '\n';
    }

};
