#include "../l/lib.h"
// #include "../l/mod.h"

class TaskF {
public:

    pii reduce(int a, int b) {
        if (a == 0) return {0,1};
        if (b == 0) return {1,0};
        if (a < 0) { a = -a; b = -b; }
        int g = gcd(a,abs(b));
        return {a/g, b/g};
    };

    pii canon (pii p, pii q) {
        int a = p.x - q.x;
        int b = p.y - q.y;
        return reduce(a,b);
    };

    void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    map<ll, unordered_set<pii>> L;
    unordered_map<pii, int> P;
    unordered_map<pii, int> W;
    
    int cur = 0;
    for (int i = 0; i < N; ++i) {
        int t,x,y; cin >> t >> x >> y;
        pii q{x,y};
        if (t == 1) {
            ll sq = ll(x)*x + ll(y)*y;
            for (pii p: L[sq]) P[canon(p,q)]++;
            W[reduce(x, y)]++;
            L[sq].insert(q);
            cur++;
        } else if (t == 2) {
            ll sq = ll(x)*x + ll(y)*y;
            L[sq].erase(q);
            for (pii p: L[sq]) P[canon(p,q)]--;
            W[reduce(x,y)]--;
            cur--;
        } else if (t == 3) {
            pii p = reduce(-y, x);
            q = reduce(x, y);
            cout << cur - 2*P[p] - W[q] << '\n';
        }
    }
}
};
