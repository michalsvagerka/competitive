#include "../l/lib.h"

class BUniqueness {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int Ans = N;
        for (int i = 0; i <= N; ++i) {
            unordered_set<int> Q;
            for (int j = 0; j < i; ++j) {
                Q.insert(A[j]);
            }
            if (Q.size() != i) continue;
            Ans = min(Ans, N - i);
            for (int k = N-1; k >= i; --k) {
                if (Q.count(A[k])) break;
                Q.insert(A[k]);
                Ans = min(Ans, k - i);
            }
        }
        cout << Ans << endl;
    }
};
