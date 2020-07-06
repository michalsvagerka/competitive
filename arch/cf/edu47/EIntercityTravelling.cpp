#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class EIntercityTravelling {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        FF ans = 0;
        FF lo = FF{1}/2;
        vector<FF> B(N+1, 1);
        for (int i = 1; i <= N; ++i) B[i] = B[i-1] * lo;
        for (int i = 0; i < N; ++i) {
            ans += B[i+1]*A[i]*(N-1-i);
            ans += B[i]*A[i];
        }
        cout << ans * FF{2}.pow(N-1) << '\n';
    }
};
