#include "../l/lib.h"
#include "../l/consttree.h"

class BSortingASegment {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> P(N); cin >> P;
        ConstTree<int, MinQOp<int>> L(P);
        ConstTree<int, MaxQOp<int>> R(P);
        int ans = N-K+1;
        for (int i = 0; i+K < N; ++i) {
            if (P[i] < L.get(i+1, i+K-1) && P[i+K] > R.get(i+1, i+K-1)) {
                --ans;
            }
        }

        bool same = false;
        int l = 1;
        for (int i = 1; i < N; ++i) {
            if (P[i] > P[i-1]) {
                l++;
                if (l == K) {
                    same = true;
                    --ans;
                }
            } else {
                l = 1;
            }
        }
        cout << ans + same << endl;
    }
};
