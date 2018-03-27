#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        set<int> C(A.begin(),A.end());
        if (A.size() != C.size()) {
            cout << "-1\n";
        }

        vector<int> B(N);
        for (int i = 0; i < N; ++i) {
            auto it = next(C.find(A[i]));
            if (it == C.end()) {
                B[i] = *C.begin();
            } else {
                B[i] = *it;
            }
        }

        cout << B;
    }
};
