#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    vector<int> fact(int x) {
        vector<int> F;
        for (int i = 2; i*i <= x; ++i) {
            if (x%i == 0) {
                F.push_back(i);
                while (x%i == 0) x/=i;
            }
        }
        if (x!=1) F.push_back(x);
        return F;
    }

void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<pii> A(N); cin >> A;
    if (N == 1) {
        cout << A[0].x << '\n';
        return;
    }

    vector<int> F = fact(A[0].x), G = fact(A[0].y);
    ll g = ll(A[1].x)*A[1].y;
    for (int i = 2; i < N; ++i) {
        g = gcd(g, ll(A[i].x)*A[i].y);
    }
    
    for (int f:F) if (g%f==0) { cout << f << endl; return; }
    for (int f:G) if (g%f==0) { cout << f << endl; return; }
    cout << -1 << endl;
}
};
