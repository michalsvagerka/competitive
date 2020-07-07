#include "../../../l/lib.h"

class DSonyaAndMatrix {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        vector<int> A(T); cin >> A;
        int mx = *max_element(A.begin(),A.end());
        vector<int> C(T, 0);
        for (int i = 0; i < T; ++i) C[A[i]]++;

        for (int w = 1; w*w <= T; ++w) {
            if (T%w != 0) continue;
            int h = T/w;
            for (int l = 0; 2*l < w; ++l) {
                int t = mx - (w-l-1);
                if (l > mx) continue;
                if (t < 0) continue;
                if (t >= h) continue;
                int b = h - t - 1;
                vector<int> CC(mx+1, 0);
                for (int k = 0; k < w; ++k) {
                    int g = abs(k-l);
                    CC[g]++;
                    CC[g+1]++;
                    if (g + t + 1 <= mx) CC[g+t+1]--;
                    if (g + b + 1 <= mx) CC[g+b+1]--;
                }
                for (int i = 0; i < mx; ++i) {
                    CC[i+1] += CC[i];
                }

                bool ok = true;
                for (int i = 0; i <= mx; ++i) {
                    ok &= C[i] == CC[i];
                }
                if (ok) {
                    cout << w << ' ' << h << '\n' << l+1 << ' ' << t+1 << '\n';
                    return;
                }
            }

        }
        cout << -1 << endl;
    }
};
