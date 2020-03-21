#include "../l/lib.h"

class BUrbanization {
public:
    void solve(istream& cin, ostream& cout) {
        int N, N1, N2; cin >> N >> N1 >> N2;
        vector<int> A(N);
        cin >> A;
        sort(A.begin(),A.end());
        if (N2 < N1) swap(N1, N2);
        reverse(A.begin(),A.end());
        double ans = 0;
        for (int i = 0; i < N1; ++i) {
            ans += A[i] * 1. / N1;
        }
        for (int i = N1; i < N1+N2; ++i) {
            ans += A[i] * 1. / N2;
        }
        cout << fixed << setprecision(10) << ans << endl;
    }
};
