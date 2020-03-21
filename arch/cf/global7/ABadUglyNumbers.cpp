#include "../l/lib.h"

class ABadUglyNumbers {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int i = 0; i < T; ++i) {
            int N; cin >> N;
            if (N == 1) {
                cout << -1 << '\n';
            } else if (N%3 == 1) {
                cout << string(N-2, '5') << "63" << '\n';
            } else {
                cout << string(N-1, '5') << '3' << '\n';
            }
        }
    }
};
