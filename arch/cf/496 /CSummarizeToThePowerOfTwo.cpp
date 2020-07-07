#include "../../../l/lib.h"

class CSummarizeToThePowerOfTwo {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        set<int> B;
        vector<bool> Good(N, false);
        for (int i = 0; i < N; ++i) {
            bool found = false;
            for (int j = 0; j <= 30; ++j) {
                Good[i] = Good[i] || (B.find((1<<j)-A[i]) != B.end());
            }
            B.insert(A[i]);
        }

        B.clear();
        for (int i = N-1; i >= 0; --i) {
            bool found = false;
            for (int j = 0; j <= 30; ++j) {
                Good[i] = Good[i] || (B.find((1<<j)-A[i]) != B.end());
            }
            B.insert(A[i]);
        }

        cout << count(Good.begin(),Good.end(),false) << '\n';
    }
};
