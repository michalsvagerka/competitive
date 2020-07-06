#include "../l/lib.h"

class BIceRinkGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        if (A[N-1] != 2) {
            cout << "-1\n";
            return;
        }

        ll lo = 2, hi = 2;
        for (int i = N-1; i >= 0; --i) {
            if ((lo+A[i]-1)/A[i]>hi/A[i]) {
                cout << "-1\n";
                return;
            }
            lo = (lo+A[i]-1)/A[i]*A[i];
            hi = hi/A[i]*A[i]+A[i]-1;
        };

        cout << lo << ' ' << hi << endl;
    }
};
