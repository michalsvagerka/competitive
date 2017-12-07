#include "../l/lib.h"
// #include "../l/mod.h"

class bobuzly {
public:
    void solve(istream& cin, ostream& cout) {
        int N,D; cin >> N >> D;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        int i = 0;
        while (i < N && A[i] < 3*D) ++i;
        int three = 2*D;
        for (int j = i; j < N; ++j) {
            three += A[j] - 2*D;
        }
        if (three == 2*D) three = 0;

        int two = 0;
        if (i > 1 && A[i-2] > 2*D) {
            two = A[i-2] + A[i-1] - 2*D;
        } else if (i > 0 && A[i-1] > 2*D) {
            two = A[i-1];
        }

        cout << max(max(three, two),max(A.back(),three+two-2*D)) << endl;
    }
};
