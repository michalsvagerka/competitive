#include "../l/lib.h"

class ForegoneSolution {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string A; cin >> A;
            int N = A.size();
            string B = A;
            for (int i = 0; i < N; ++i) {
                if (A[i] == '4') {
                    A[i] = B[i] = '2';
                } else {
                    B[i] = '0';
                }
            }
            int j = 0;
            while (B[j] == '0') j++;
            cout << "Case #" << t+1 << ": " << A << ' ' << B.substr(j) << endl;
        }
    }
};
