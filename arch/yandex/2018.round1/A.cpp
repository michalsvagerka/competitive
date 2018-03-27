#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int K,N; cin >> N >> K;
        int u = (N+K)/(K+1);
        if (N%(K+1) == 1) {
            cout << 2*u - 1 << endl;
        } else {
            cout << 2 * u << endl;
        }
    }
};
