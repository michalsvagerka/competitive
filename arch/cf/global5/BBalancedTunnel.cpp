#include "../../../l/lib.h"

class BBalancedTunnel {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), B(N);
        cin >> A >> B;
        vector<int> IA(N), IB(N);
        for (int i = 0; i < N; ++i) {
            IA[A[i]-1] = i;
        }

        for (int i = 0; i < N; ++i) B[i] = IA[B[i]-1];
        
        vector<bool> U(N);
        int P = 0, ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += P != B[i];
            U[B[i]] = true;
            while (P < N && U[P]) P++;
        }
        cout << ans << endl;
    }
};
