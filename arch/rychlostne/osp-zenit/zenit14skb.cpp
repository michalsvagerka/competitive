#include "../l/lib.h"

class zenit14skb {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N, 1);
        for (int i = 1-N%2; i < N; i += 2) {
            A[i] = i/2 + 2;
        }
        cout << A;
    }
};
