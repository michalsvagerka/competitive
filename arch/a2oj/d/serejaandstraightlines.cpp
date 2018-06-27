#include "../../../l/lib.h"
 #include "../../../l/consttree.h"

class serejaandstraightlines {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pair<ll,ll>> P(N); cin >> P;
        sort(P.begin(),P.end(),[](const pair<ll,ll>&p, const pair<ll,ll>&q) {
            return p.y - p.x < q.y - q.x;
        });
        vector<ll> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            A[i] = -P[i].x + P[i].y;
            B[i] = P[i].x + P[i].y;
        }
//        cout << A << B;
        ConstTree<ll,MinQOp<ll>> LOB(B);
        ConstTree<ll,MaxQOp<ll>> HIB(B);

        ll ans = bsl(0LL, 4000000000LL, [&](ll x) {
            int e = 0;
            for (int b = 0; b < N; ++b) {
                while (e < N && A[e] - A[b] <= x) ++e;
                ll lo = std::numeric_limits<ll>::max();
                ll hi = std::numeric_limits<ll>::min();
                if (b != 0) { lo = min(lo, LOB.get(0, b-1)); hi = max(hi, HIB.get(0, b-1)); }
                if (e != N) { lo = min(lo, LOB.get(e, N-1)); hi = max(hi, HIB.get(e, N-1)); }
//                cout << b << ' ' << e << ' ' << lo << ' ' << hi << ' ' << x << endl;
                if (hi <= lo + x) return true;
            }
            return false;
        });

        cout << fixed << setprecision(15) << ans / 2.0 << '\n';

    }
};
