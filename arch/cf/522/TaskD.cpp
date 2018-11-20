#include "../l/lib.h"
 #include "../l/consttree.h"

constexpr int L = 20;

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    if (N == 1) {
        cout << 0 << endl;
        return;
    }
    
    vector<int> R(N); cin >> R;
    vector2<int> Lo(L, 3*N), Hi(L, 3*N);
    for (int i = 0; i < 3*N; ++i) {
        Lo[0][i] = max(0, i - R[i%N]);
        Hi[0][i] = min(3*N-1, i + R[i%N]);
    }

    ConstTree<int, MinQOp<int>> LO(Lo[0]);
    ConstTree<int, MaxQOp<int>> HI(Hi[0]);
    for (int l = 1; l < L; ++l) {
        for (int i = 0; i < 3 * N; ++i) {
            Lo[l][i] = LO.get(Lo[l-1][i], Hi[l-1][i]);
            Hi[l][i] = HI.get(Lo[l-1][i], Hi[l-1][i]);
        }
        
        LO.update(Lo[l]);
        HI.update(Hi[l]);
    }

    vector<int> Ans(N, 1), Left(N, 0), Right(N, 0);
    for (int i = 0; i < N; ++i) Left[i] = Right[i] = N+i;
    
    for (int l = L-1; l >= 0; --l) {
        LO.update(Lo[l]);
        HI.update(Hi[l]);
        
        for (int i = 0; i < N; ++i) {
            int lo = Left[i];
            int hi = Right[i];
            int x = LO.get(lo, hi);
            int y = HI.get(lo, hi);
            if (y - x < N-1) {
                Ans[i] += 1<<l;
                Left[i] = x;
                Right[i] = y;
            }
        }
    }

    cout << Ans;
}
};
