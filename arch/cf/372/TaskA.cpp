#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;

    cout << 2 << endl;
    for (int i = 2; i <= N; ++i) {
        cout << ll(i+1) * ll(i+1) * ll(i) - (ll(i) - 1) << '\n';
    }
}
};
