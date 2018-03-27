#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        ll K, D, T; cin >> K >> D >> T;

        cout << fixed << setprecision(14);
        ll switchEvery = (K+D-1)/D;
        ll time = switchEvery * D;
        double cookingPower = K + (time-K)/2.0;
        double iters = floor(T / cookingPower);
        double left = T - iters*cookingPower;
        if (left < K) {
            cout << iters*D*switchEvery + left << endl;
        } else {
            cout << iters*D*switchEvery + K + 2*(left-K) << endl;
        }
    }
};
