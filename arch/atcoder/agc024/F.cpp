#include "../../../l/lib.h"
// #include "../l/mod.h"

class F {
public:

    int ans;
    unordered_set<pair<pii,pii>> Q;
    void gen(int L, int M, int N, int l, int m) {
        if (Q.find({{L,M},{l,m}}) != Q.end()) return;
        Q.insert({{L,M},{l,m}});
        if (L == N) {
            ans++;
            return;
        }
        gen(L+1, M<<1, N, l, m);
        gen(L+1, (M<<1)|1, N, l, m);
        gen(L+1, M<<1, N, l+1, m<<1);
        gen(L+1, (M<<1)|1, N, l+1, (m<<1)|1);
    }

    void solve(istream& cin, ostream& cout) {
        ans = 0;
        gen(0, 0, 12, 0, 0);
        cout << ans << endl;
    }
};
