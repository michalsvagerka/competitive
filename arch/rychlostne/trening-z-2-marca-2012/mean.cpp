#include "../l/lib.h"
// #include "../l/mod.h"

class mean {
public:
    void solve(istream& cin, ostream& cout) {
        int n; cin >> n;
        string q, s; cin >> q >> s;
        if (q>s) swap(q,s);
        vector<int> R(n,0);
        if (q=="median") {
            for (int i = n/2; i < n; ++i) R[i] = 100;
            if (n%2) {
                R[n/2] = 99;
            } else {
                R[n/2-1] = 1;
            }
        } else if (s=="median") {
            for (int i = n/2; i < n; ++i) R[i] = 100;
        } else {
            int best = 0;
            for (int z = 1; z <= n/2; ++z) {
                vector<int> Z(n,0);
                int s = 0;
                for (int i = 0; i < n - z; ++i) {
                    Z[n - i - 1] = 100 - i/z;
                    s += 100 - i/z;
                }
                if (s > best) {
                    best = s;
                    swap(R,Z);
                }
            }
        }
        cout << R;
    }
};
