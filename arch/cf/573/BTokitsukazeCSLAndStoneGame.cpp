#include "../l/lib.h"

class BTokitsukazeCSLAndStoneGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        int red = -1;
        for (int i = 0; i < N-1; ++i) {
            if (i+2 != N && A[i] == A[i+2]) {
                cout << "cslnb\n";
                return;
            }

            if (A[i] == A[i+1]) {
                if (A[i] == 0) {
                    cout << "cslnb\n";
                    return;
                }

                if (i != 0 && A[i-1] + 1 == A[i]) {
                    cout << "cslnb\n";
                    return;
                }

                if (red != -1) {
                    cout << "cslnb\n";
                    return;
                }

                red = i;
            }
        }

        ll tot = 0;
        for (int a: A) tot += a;
        tot -= ll(N)*ll(N-1)/2;
        if (tot%2==1) {
            cout << "sjfnb\n";
        } else {
            cout << "cslnb\n";
        }
    }
};
