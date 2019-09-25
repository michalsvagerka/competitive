#include "../l/lib.h"
#include "../l/consttree.h"

class FGardenerAlex {
public:
    vector<int> A, I;
    ConstTree<int, MinQOp<int>> MQ{vector<int>{1}};

    int depth(int l, int r) {
        if (l > r) return 0;
//        if (k == 0) return false;
        int m = MQ.get(l,r);
        int i = I[m];
        return max(depth(l, i-1), depth(i+1, r)) + 1;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) {
            cout << 1 << ' ' << 0 << endl;
            return;
        }
        
        A.resize(N); cin >> A;
        int one = -1;
        for (int i = 0; i < N; ++i) {
            if (A[i] == 1) one = i;
            --A[i];
        }

        rotate(A.begin(),A.begin()+one,A.end());

        I.resize(N);
        for (int i = 0; i < N; ++i) I[A[i]] = i;

        MQ = ConstTree<int, MinQOp<int>>{A};

        int K = bsl(0, N, [&](int k) {
            int w = bsh(1, N-1, [&](int r) { return depth(1, r) <= k; });
            if (w == -1) return false;
            return depth(w+1, N-1) <= k;
        });

        int w = bsh(1, N-1, [&](int r) {
            return depth(1, r) <= K;
        });

        cout << K+1 << ' ' << (w + one + 1)%N << endl;
    }
};
