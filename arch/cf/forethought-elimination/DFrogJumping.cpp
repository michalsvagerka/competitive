#include "../l/lib.h"

class DFrogJumping {
public:
    void solve(istream& cin, ostream& cout) {
        int M, A, B; cin >> M >> A >> B;
        int G = gcd(A,B);
        vector<int> R{0};
        int r = 0, mx = 0;
        vector<int> S(A+B, -1);
        S[0] = 0;
        do {
            if (r >= B) r -= B;
            else r += A;
            R.push_back(r);
            mx = max(mx, r);
            S[r] = mx;
        } while (r != 0);
        S[0] = 0;

        ll ans = 0;
        for (int i = 0; i < A+B; ++i) {
            if (S[i] != -1 && S[i] <= M) {
                ans += M - S[i] + 1;
            }
        }


        if (M >= A+B) {
            int c = (M-A-B)/G+1;
            ans += ll(c-1) * ll(c) * G / 2;
            ans += ll(c) * (M%G + 1);
        }

        cout << ans << endl;
    }
};
