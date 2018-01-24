#include "../l/lib.h"
#include "../l/consttree.h"

class smoothie {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        vector<int> Z(N+1, 0);
        for (int i = 0; i < N; ++i) {
            Z[i+1] = Z[i] + (S[i] == 'p') - (S[i] == 'j');
        }

        ConstTree<int, MinOp<int>> M(Z);
        ConstTree<int, MaxOp<int>> R(Z);
        vector<int> Q(N+1), T(N+1), J(N+1);
        for (int i = 0; i < N; ++i) Q[i] = bsh(i, N, [&](int j) { return M.get(i,j) >= Z[i]; });
        for (int i = 1; i <= N; ++i) T[i] = bsl(0, i, [&](int j) { return R.get(j,i) <= Z[i]; });
        ConstTree<int, MinOp<int>> W(T);
        for (int i = 0; i < N; ++i) J[i] = bsh(i, Q[i], [&](int j) { return W.get(j,Q[i]) <= i; });
//        cout << Q << T << J;

        int ans = 0;
        for (int i = 0; i < N; ++i) ans = max(ans, J[i]-i);
        cout << ans << endl;
    }
};
