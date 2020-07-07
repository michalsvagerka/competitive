#include "../../../l/lib.h"

class AFingerprints {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N), B(M); cin >> A >> B;
        vector<int> C;
        for (int i = 0; i < N; ++i) {
            if (count(B.begin(),B.end(),A[i]) > 0) C.push_back(A[i]);
        }
        cout << C;
    }
};
