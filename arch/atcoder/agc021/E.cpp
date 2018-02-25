#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<998244353> T;

#define comb(n,k) (((k)>=0&&(k)<=(n)) ? F[(n)] * I[(n)-(k)] * I[(k)] : 0)
class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        auto F = T::fact(2*K);
        auto I = T::invfact(2*K);
        T ans = 0;
        for (int r = max(N, K - K/2); r <= K; ++r) {
            int b = K - r;
            ans += comb(K-(r==b), r) - comb(K-(r==b), b+N-r-1-(r==b));
        }

        cout << ans << endl;
    }
};
