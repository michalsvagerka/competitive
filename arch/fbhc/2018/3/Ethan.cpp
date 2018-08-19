#include "../l/lib.h"
// #include "../l/mod.h"

class Ethan {
public:
void solve(istream& cin, ostream& cout) {

    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int M,K; cin >> M >> K;
        vector<int> A(M); cin >> A;
        int ans = 0;
        for (int c = 0; c <= (2*M-1)*K; ++c) {
            int best = 0;
            vector<int> W(2*M+1, 0);
            for (int i = 0; i < 2*M-1; ++i) {
                int lo = 0, hi = 0;
                for (int j = i; j <= 2*M-1; ++j) {
                    int k = j;
                    if (k == 2*M-1 || (k%2 == 0 && A[k/2] < 0) || (k%2==1)) {
                        best = max(best, W[i] + min(hi, c));
                        int mod = 0;
                        if (k == 2*M-1) {} else if (k%2==0) { mod = A[k/2]; } else { mod = -1; }
                        W[k+1] = max(W[k+1], W[i] + min(hi, c) + mod);
                    }
                    if (j == 2*M-1) break;

                    if (j%2 == 0) {
                        if (A[j/2] < 0) break;
                        lo += A[j/2]; hi += A[j/2];
                        if (lo > c) break;
                    }
                    else { hi += K; }
                }
            }

            ans = max(ans, best - c);
        }

        cout << "Case #" << t+1 << ": " << ans << '\n';
    }

}
};
