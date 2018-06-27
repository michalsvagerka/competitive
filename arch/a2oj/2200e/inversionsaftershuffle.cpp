#include "../l/lib.h"
 #include "../l/fenwick.h"

class inversionsaftershuffle {
public:
    void solve(istream& cin, ostream& cout) {
        int N;
        cin >> N;
        vector<int> A(N); cin >> A;
        for (int &a:A) --a;

        Fenwick<ll> C(N+1,0), CX(N+1,0);

        double choices = ll(N)*(N+1)/2;

        double ans = 0;
        for (int j = 0; j < N; ++j) {
            ll s = C.range(A[j]+1, N+1);
            ll sx = CX.range(A[j]+1, N+1);

            double me = choices * s - (N-j) * (sx + s);
            ans += me;

            C.add(A[j], 1);
            CX.add(A[j], j);
        }

        for (int i = 1; i <= N; ++i) {
            ans += double(N-i+1) * i * (i-1) / 4.0;
        }

        cout << fixed << setprecision(10) << ans/choices << endl;

    }
};
