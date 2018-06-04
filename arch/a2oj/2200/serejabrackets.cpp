#include "../l/lib.h"
#include "../l/consttree.h"

class serejabrackets {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = int(S.size());
        vector<int> P(N+1, 0);
        for (int i = 0; i < N; ++i) {
            P[i+1] = P[i] + (S[i] == '(') - (S[i] == ')');
        }

        int M; cin >> M;
        ConstTree<int, MinQOp<int>> T(P);
        for (int i = 0; i < M; ++i) {
            int l, r; cin >> l >> r;
            --l;
            cout << r-l-P[l]-P[r]+2*T.get(l,r) << '\n';
//            cout << P[l] << ' ' << P[r] << ' ' << T.get(l,r) << endl;
        }



    }
};
