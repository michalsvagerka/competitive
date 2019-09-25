#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/consttree.h"

class PancakePyramid {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int S; cin >> S;
            vector<int> A(S); cin >> A;
            vector<FieldMod> P(S + 1, 0);
            FieldMod ans = 0;
            for (int k = 0; k < 2; ++k) {
                for (int i = 0; i < S; ++i) P[i + 1] = P[i] + A[i];
                ConstTree<int, MaxQOp<int>> CT(A);
                for (int i = 0; i < S - 1; ++i) {
                    int l = i == 0 ? -1 : bsh(0, i - 1, [&](int j) { return CT.get(j, i - 1) > A[i]; });
                    int r = bsl(i + 1, S - 1, [&](int j) { return CT.get(i + 1, j) >= A[i]; });
                    if (r != -1) {
                        FieldMod cur = FieldMod{A[i]} * FieldMod{r - i} - (P[r] - P[i]);

                        if (A[r] == A[i]) {
                            if (k == 1) {
                                int rr = bsl(i+1, S - 1, [&](int j) { return CT.get(i + 1, j) > A[i]; });
                                if (rr == -1) rr = S;
                                ans += cur * FieldMod{rr - r} * FieldMod{l+1};
                            } else {
                                ans -= cur * FieldMod{S - r} * FieldMod{i - l};
                            }
                        }

                        ans += cur * FieldMod{S - r} * FieldMod{i - l};
                    }
                }
                reverse(A.begin(),A.end());

            }
            cout << "Case #" << t + 1 << ": " << ans << '\n';
        }
    }
};
