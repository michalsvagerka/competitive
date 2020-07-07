#include "../../../l/lib.h"

class ATanyaAndStairways {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> B;
        for (int i = 0; i < N; ++i) {
            if (i == N-1 || A[i] >= A[i+1]) B.push_back(A[i]);
        }
        cout << B.size() << '\n' << B;
    }
};
