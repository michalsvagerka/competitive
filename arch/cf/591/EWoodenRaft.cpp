#include "../../../l/lib.h"

constexpr int M = 5e5 + 2;

class EWoodenRaft {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        ll tot = 0;
        vector<int> F(M, -1);
        F[M-1] = N;
        for (int i = 0; i < N; ++i) {
            if (F[A[i]] == -1) F[A[i]] = i;
            tot += A[i];
        }

        for (int i = M-1; i >= 0; --i) {
            if (F[i] == -1) F[i] = F[i+1];
        }

        ll ans = 0;
        for (int y = M; y >= 2; --y) {
            int x = bsh(2, M, [&](int x) {
                int a = 0, b = -1e9, c = -1e9;
                for (int j = 0, k = 0; j < M; j += y, k++) {
                    int g = F[j], h = F[min(j+y, M-1)], s = (h-g)*k;
                    a += s; b += s; c += s;
                    if (h - g >= 2 && A[h-2] >= x) c = max(c, a - 2*k + (A[h-2]-x)/y + (A[h-1]-x)/y);
                    if (h - g >= 1 && A[h-1] >= 2*x) c = max(c, a - k + (A[h-1]-2*x)/y);
                    if (h - g >= 1 && A[h-1] >= x) {
                        c = max(c, b - k + (A[h-1]-x)/y);
                        b = max(b, a - k + (A[h-1]-x)/y);
                    }
                    if (c >= x) return true;
                }
                return false;
            });
            ans = max(ans, x * ll(y));
        }
        cout << ans << endl;
    }
};
