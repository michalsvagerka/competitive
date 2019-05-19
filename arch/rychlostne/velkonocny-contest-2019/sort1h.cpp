#include "../l/lib.h"

class sort1h {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<bool> U(N, false);
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (!U[i]) {
                int j = i;
                int l = 0;
                while (!U[j]) {
                    U[j] = true;
                    j = A[j];
                    l++;
                }
                if (l != 1) {
                    ans += l+1;
                }
            }
        }
        cout << ans << '\n';
    }
};
