#include "../../../l/lib.h"

class BLimericks {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> F;
        for (int i = 2; i < N; ++i) {
            if (N%i==0) {
                cout << i << N/i << '\n';
                return;
            }
        }
    }
};
