#include "../l/lib.h"

class FIntegerGame {
public:
    void solve(istream& cin, ostream& cout) {
        vector<ll> A(3); cin >> A;
        cout << "First" << endl;
        int prev = -1;
        while (true) {
            ll lo = *min_element(A.begin(),A.end());
            ll hi = *max_element(A.begin(),A.end());
            ll mid = A[0]+A[1]+A[2] - lo - hi;
            ll top = hi-mid;
            ll bot = mid-lo;
            ll q = -1;
            if (top == bot) {
                q = top;
            } else if (prev != -1 && A[prev] == hi) {
                q = 2*top + bot;
            } else {
                q = bot+top;
            }
            cout << q << endl;
            int x; cin >> x;
            if (x <= 0) {
                break;
            } else {
                A[x-1] += q;
            }
//            cerr << A;
            prev = x-1;
        }
    }
};
