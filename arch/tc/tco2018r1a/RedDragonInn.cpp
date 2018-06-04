#include "../../../l/lib.h"
// #include "../l/mod.h"

class RedDragonInn {
public:
    int maxGold(int N, int X) {
        return bsh(0, 1000000000, [&](int s) {
            int t = s/2;
            int l = t/N;
            return l <= X;
        });
    }

    void solve(istream& cin, ostream& cout) {
        int N,X; cin >> N >> X;
        cout << maxGold(N,X) << endl;
    }
};
