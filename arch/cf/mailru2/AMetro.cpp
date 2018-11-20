#include "../l/lib.h"
// #include "../l/mod.h"

class AMetro {
public:
void solve(istream& cin, ostream& cout) {
    int N, S; cin >> N >> S;
    vector<int> A(N), B(N);
    cin >> A >> B;
    --S;
    if (!A[0]) { cout << "NO\n"; }
    else if (A[S]) { cout << "YES\n"; }
    else {
        for (int j = S+1; j < N; ++j) {
            if (A[j] && B[j] && B[S]) {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
    }
}
};
