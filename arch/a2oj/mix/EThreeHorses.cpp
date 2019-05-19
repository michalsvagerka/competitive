#include "../l/lib.h"
// #include "../l/mod.h"

class EThreeHorses {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; 
    cin >> N >> M;
    vector<int> A(N); cin >> A;
    int g = A[0]-1;
    for (int i = 1; i < N; ++i) {
        g = gcd(g, A[i]-1);
    }
    while (g%2==0) g/=2;
    vector<int> D;
    for (int i = 1; i*i <= g; ++i) {
        if (g%i==0) {
            D.push_back(i);
            if (i*i != g) D.push_back(g/i);
        }
    }
    ll ans = 0;
    for (int d: D) {
        while (d <= M) {
            ans += M - d;
            d *= 2;
        }
    }
    cout << ans << endl;
}
};
