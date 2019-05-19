#include "../l/lib.h"

class CThanosNim {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        bool same = true;
        for (int i = 0; i < N; i += 2) {
            same &= A[i] == A[i+1];
        }

        if (A[0] == A[N/2]) {
            cout << "Bob\n";
            return;
        }

        cout << "Alice\n";
    }
};
