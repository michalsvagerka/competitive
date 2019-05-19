#include "../l/lib.h"

class AThanosSort {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        for (int r = N; r >= 1; r/=2) {
            for (int i = 0; i < N; i += r) {
                bool ok = true;
                for (int j = i+1; j < i + r; ++j) {
                    ok &= A[j] >= A[j-1];
                }
                if (ok) {
                    cout << r << endl;
                    return;
                }
            }
        }
    }
};
