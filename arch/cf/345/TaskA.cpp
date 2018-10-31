#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    map<int, int> X, Y;
    map<pii, int> Q;

    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        int x, y; cin >> x >> y;
        ans += X[x];
        ans += Y[y];
        ans -= Q[{x,y}];
        X[x] ++;
        Y[y] ++;
        Q[{x,y}]++;
    }
    
    cout << ans << endl;
    
}
};
