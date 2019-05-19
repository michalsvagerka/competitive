#include "../l/lib.h"

class DPigeonDOr {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        
        int t = A[2];
        sort(A.begin(),A.end());
        cout << 2+(t^A[0]) << endl;
    }
};
