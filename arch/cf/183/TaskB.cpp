#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, X, Y, A, B;
    cin >> N >> M >> X >> Y >> A >> B;
    int g = gcd(A, B);
    A /= g; B /= g;
    int fact = min(N/A, M/B);
    A *= fact; B *= fact;
    int X1 = max(0, min(X-(A+1)/2, N-A));
    int Y1 = max(0, min(Y-(B+1)/2, M-B));
    cout << X1 << ' ' << Y1 << ' ' << X1+A << ' ' << Y1+B << endl;
}
};
