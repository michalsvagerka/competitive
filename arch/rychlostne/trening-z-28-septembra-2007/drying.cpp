#include "../l/lib.h"
// #include "../l/mod.h"

class drying {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int K; cin >> K;
        sort(A.begin(),A.end());
        if (K == 1) {
            cout << A.back() << endl;
            return;
        }

        int ans = bsl(0, 1000000000, [&](int q) {
            ll rad = 0;
            for (int i = 0; i < N; ++i) {
                if (A[i] > q) rad += (A[i]-q+K-2)/(K-1);
            }
            return rad <= q;
        });
        cout << ans << endl;
    }
};
