#include "../l/lib.h"
// #include "../l/mod.h"

class CaissaAndSugar {
public:
void solve(istream& cin, ostream& cout) {
    int N,S; cin >> N >> S;
    S *= 100;
    int Ans = -1;
    for (int i = 0; i < N; ++i) {
        int x,y; cin >> x >> y;
        int t = 100*x + y;
        if (t > S) continue;
        int v = t % 100;
        Ans = max(Ans, v == 0 ? 0 : (100 - v));
    }
    cout << Ans << endl;

}
};
