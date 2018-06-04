#include "../../../l/lib.h"
#include "../../../l/frac.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N, X; cin >> N >> X;
        vector<ll> L(N), S(N); cin >> L >> S;

        maxheap<pair<Fraction,int>> H;
        for (int i = 0; i < N; ++i) {
            H.push({Fraction{L[i],(ll)S[i]*(S[i]+1)}, i});
        }

        for (int x = 0; x < X; ) {

            auto h = H.top();
            H.pop();

            int i = h.y;
            int t = max(1, min(50, (X-x) / (4*N)));
//            int t = 1;
            x += t;
            S[i] += t;
            H.push({Fraction{L[i], (ll) S[i] * (S[i] + 1)}, i});
        }


        double ans = 0;
        for (int i = 0; i < N; ++i) ans += double(L[i])/S[i];
        cout << fixed << setprecision(12) << ans << endl;

    }
};
