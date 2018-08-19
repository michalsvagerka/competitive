#include "../l/lib.h"
// #include "../l/mod.h"

class Interception {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        cout << "Case #" << t+1 << ": ";
        int N; cin >> N;
        vector<int> P(N+1); cin >> P;
        cout << (N%2);
        if (N%2) cout << "\n0.0";
        cout << endl;
    }

}
};
