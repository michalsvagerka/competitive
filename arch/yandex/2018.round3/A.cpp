#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int b = __builtin_popcount(N);
        cout << b / 2 << endl;
    }
};
