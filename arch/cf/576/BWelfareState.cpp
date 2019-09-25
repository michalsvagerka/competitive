#include "../l/lib.h"
#include "../l/segtree.h"

class BWelfareState {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int Q; cin >> Q;

        SetMaxTree<int> T;
        T.setup(Q+3, 0);
        vector<int> Set(N, -1);
        for (int q = 0; q < Q; ++q) {
            int t; cin >> t;
            if (t == 1) {
                int p, x; cin >> p >> x;
                --p;
                A[p] = x;
                Set[p] = q;
            } else {
                int x; cin >> x;
                T.put(q, x);
            }
        }

        for (int i = 0; i < N; ++i) {
            int raise = T.get(Set[i]+1, Q+1);
            A[i] = max(A[i], raise);
        }

        cout << A;

    }
};
