#include "../l/lib.h"

class CVladikAndFractions {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) {
            cout << -1 << endl;
        } else {
            cout << N << ' ' << N + 1 << ' ' << N * (N + 1) << '\n';
        }
    }
};
