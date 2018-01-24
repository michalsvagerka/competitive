#include "../l/lib.h"
#include "../l/segtree.h"

class dominofall {
public:
    SetMaxTree<pii> T;

    int solve(int l, int r, int z) {
        if (z > 20 || r < l) return z;
        auto t = T.get(l, r);
        // cerr << l << ' ' << r << ' ' << -t2.y << ' ' << t1.y << endl;
        return min(solve(l, t.y-1, z+1), solve(t.y+1, r, z+1));
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i].x;
            A[i].y = i;
        }

        T.setup(A, {0,0});
        cout << solve(0, N-1, 0) << endl;
    }
};
