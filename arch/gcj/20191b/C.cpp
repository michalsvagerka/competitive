#include "../l/lib.h"
#include "../l/consttree.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int N, K; cin >> N >> K;
            vector<int> C(N), D(N);
            cin >> C >> D;
            ConstTree<int, MaxQOp<int>> MC(C), MD(D);
            ll ans = 0;
            for (int j = 0; j < N; ++j) {
                int left_geq = j == 0 ? -1 : bsh(0, j-1, [&](int x) { return MC.get(x,j-1) >= C[j]; });
                int right_gt = bsl(j, N-1, [&](int x) { return MC.get(j,x) > C[j]; });
                if (right_gt == -1) right_gt = N;

                int left_ok = bsh(0, j, [&](int x) { return MD.get(x, j) >= C[j]-K; });
                int right_ok = bsl(j, N-1, [&](int x) { return MD.get(j,x) >= C[j]-K; });
                if (right_ok == -1) right_ok = N;
                int left_bad = bsh(0, j, [&](int x) { return MD.get(x, j) > C[j]+K; });
                int right_bad = bsl(j, N-1, [&](int x) { return MD.get(j,x) > C[j]+K; });
                if (right_bad == -1) right_bad = N;

                right_bad = min(right_bad, right_gt);
                left_bad = max(left_bad, left_geq);
                
                if (right_bad >= right_ok && left_bad <= left_ok) {
                    ans += ll(right_bad - right_ok) * ll(left_ok - left_bad);
                }
                if (right_bad >= right_ok) {
                    ans += ll(right_bad - right_ok) * ll(j - max(left_ok,left_bad));
                }
                if (left_bad <= left_ok) {
                    ans += ll(left_ok - left_bad) * ll(min(right_ok,right_bad) - j);
                }
            }

            cout << "Case #" << t << ": ";
            cout << ans;
            cout << endl;
        }
    }
};
