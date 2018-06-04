#include "../../../l/lib.h"
#include "../../../l/consttree.h"

class sawseq {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        ConstTree<int, MinQOp<int>> L(A);
        ConstTree<int, MaxQOp<int>> H(A);

        map<int, set<int>> I;
        for (int i = 0; i < N; ++i) I[A[i]].insert(i);

        int ans = 0;
        int i = 0;
        while (i < N) {
            int t = bsh(i, N-1, [&](int j) { return L.get(i,j) == A[i]; });
            int m = H.get(i, t);
            int j = *prev(I[m].upper_bound(t));
            ans++;
            i = j+1;
        }


        cout << ans << endl;
    }
};
