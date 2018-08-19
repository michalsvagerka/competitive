#include "../l/lib.h"
 #include "../l/random.h"

class Ghd {
public:



void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<ll> A(N); cin >> A;
    ll ans = 1;
    random_int rr(0, N-1);
    TimeLimit tl(4);
    while (tl) {
        int p = rr(rng);
        map<ll, int> G;
        for (int i = 0; i < N; ++i) G[gcd(A[i], A[p])]++;
        vector<pair<ll,int>> R(G.begin(),G.end());

        for (int i = R.size()-1; i >= 0; --i) {
            if (R[i].x <= ans) break;
            int r = 0;
            for (int j = i; j < R.size(); ++j) {
                if (R[j].x % R[i].x == 0) {
                    r += R[j].y;
                }
            }
            if (2*r >= N) ans = R[i].x;
        }
    }
    cout << ans << endl;
}
};
