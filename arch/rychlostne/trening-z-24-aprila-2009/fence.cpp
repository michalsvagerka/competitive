#include "../l/lib.h"
// #include "../l/mod.h"

class fence {
public:
    void solve(istream& cin, ostream& cout) {
        ui N, K, M; cin >> N >> K >> M;
        vector<puu> A(M);
        for (ui i = 0; i < M; ++i) cin >> A[i].x >> A[i].y;
        sort(A.begin(),A.end());
        reverse(A.begin(),A.end());
        ll ans = 0; ui left = 0;
        for (ui i = 0; i < M; ++i) {
            if (left > A[i].y - A[i].x + 1) {
                left -= A[i].y - A[i].x + 1;
            } else {
                A[i].y -= left;
                left = 0;
                ui t = (A[i].y - A[i].x + 1) / K;
                ans += ll(t)*(2*A[i].y - (t-1)*K)/2;
                A[i].y -= t*K;
                if (A[i].y >= A[i].x) {
                    left = K - (A[i].y - A[i].x + 1);
                    ans += A[i].y;
                }
            }
        }

        cout << 2*ans << endl;
    }
};
