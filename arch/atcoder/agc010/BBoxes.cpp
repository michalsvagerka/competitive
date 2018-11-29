#include "../l/lib.h"
// #include "../l/mod.h"

class BBoxes {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    ll s = 0;
    for (int a:A) s += a;
    ll v = ll(N)*ll(N+1)/2;
    if (s % v != 0) {
        cout << "NO\n";
        return;
    }

    int rounds = s / v;
    for (int i = 0; i < N; ++i) {
        int d = A[i]-A[(i+1)%N]+rounds;
        if (d < 0 || d%N != 0) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
};
