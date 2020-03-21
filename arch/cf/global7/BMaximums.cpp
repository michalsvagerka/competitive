#include "../l/lib.h"

class BMaximums {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> B(N); cin >> B;
        vector<int> X(N+1, 0), A(N);
        for (int i = 0; i < N; ++i) {
            A[i] = B[i] + X[i];
            X[i+1] = max(X[i], A[i]);
        }
        cout << A;
    }
};
