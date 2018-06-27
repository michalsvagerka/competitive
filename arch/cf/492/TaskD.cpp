#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    int R; cin >> R;
    vector<int> C(1<<N); cin >> C;
    ll tot = 0;
    for (int c:C) tot += c;
    cout << fixed << setprecision(10) << double(tot)/(1<<N) << '\n';
    for (int i = 0; i < R; ++i) {
        int z,g; cin >> z >> g;
        tot -= C[z];
        tot += g;
        C[z] = g;
        cout << double(tot)/(1<<N) << '\n';
    }
}
};
