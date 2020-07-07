#include "../../../l/lib.h"
#include "../../../l/segtree.h"

class ofarbipas1 {
public:
    void solve(istream& cin, ostream& cout) {
        int P, F; cin >> P >> F;
        vector<int> A(P); cin >> A;
        for (int&a: A) --a;
        vector<int> LO(F, P), HI(F, -1);
        for (int i = 0; i < P; ++i) {
            LO[A[i]] = min(LO[A[i]], i);
            HI[A[i]] = max(HI[A[i]], i);
        }
        vector<vector<int>> I;
        vector<bool> U(F, false);
        for (int i = 0; i < P; ++i) {
            if (!U[A[i]]) {
                I.push_back({A[i]+1, LO[A[i]]+1, HI[A[i]]+1});
                U[A[i]] = true;
            }
        }

        AssignMaxTree<int> S;
        S.setup(P, 0);
        for (int i = 0; i < I.size(); ++i) {
            S.put(I[i][1]-1, I[i][2]-1, i+1);
        }
        vector<int> B(P);
        for (int j = 0; j < P; ++j) {
            B[j] = I[S.get(j)-1][0] - 1;
        }
        
        if (A == B) {
            cout << I.size() << '\n';
            for (auto &i: I) cout << i;
        } else {
            cout << "-1\n";
        }
    }
};
