#include "../l/lib.h"

class ABalloons {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        if (N == 1 || (N == 2 && A[0] == A[1])) cout << "-1\n";
        else {
            int tot = accumulate(A.begin(),A.end(),0);
            if (2*A[0] == tot) cout << "2\n1 2\n";
            else cout << "1\n1\n";
        }
    }
};
