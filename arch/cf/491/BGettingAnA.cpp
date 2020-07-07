#include "../../../l/lib.h"

class BGettingAnA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        for (int i = 0; i <= N; ++i) {
            int s = accumulate(A.begin(),A.end(),0);
            if (2 * s >= 9 * N) {
                cout << i << endl;
                return;
            } else A[i] = 5;
        }
    }
};
