#include "../l/lib.h"
// #include "../l/mod.h"

class AAddition {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    int c = 0;
    for (int a:A) c += a%2;
    cout << (c%2?"NO":"YES") << endl;
}
};
