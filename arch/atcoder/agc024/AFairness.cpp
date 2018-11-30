#include "../l/lib.h"
// #include "../l/mod.h"

class AFairness {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, C; cin >> A >> B >> C;
        ll K; cin >> K;
        if (K % 2 == 0) cout << A-B << endl;
        else cout << B-A << endl;
    }
};
