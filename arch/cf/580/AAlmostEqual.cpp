#include "../l/lib.h"

class AAlmostEqual {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N%2 == 1) {
            vector<int> A(2*N);
            for (int i = 0; i < N; ++i) {
                if (i%2 == 0) {
                    A[i] = 2*i+1;
                    A[N+i] = 2*i+2;
                } else {
                    A[i] = 2*i+2;
                    A[N+i] = 2*i+1;
                }
            }
            cout << "YES\n" << A;
        } else {
            cout << "NO\n";
        }
    }
};
