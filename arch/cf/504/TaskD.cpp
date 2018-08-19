#include "../l/lib.h"
#include "../l/consttree.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, Q; cin >> N >> Q;
    vector<int> A(N);
    cin >> A;

    bool hasZero = false;
    bool hasMax = false;
    for (int i = 0; i < N; ++i) {
        hasMax |= A[i] == Q;
        hasZero |= A[i] == 0;
    }
    if (!hasMax && !hasZero) {
        cout << "NO\n";
        return;
    }
    if (!hasMax) {
        for (int i = 0; i < N; ++i) {
            if (A[i] == 0) {
                A[i] = Q;
                break;
            }
        }
    }

    for (int i = 0; i < N-1; ++i) if (A[i+1] == 0) A[i+1] = A[i];
    for (int i = N-1; i > 0; --i) if (A[i-1] == 0) A[i-1] = A[i];
    
    vector<int> LO(Q+1, N), HI(Q+1, -1);
    for (int i = 0; i < N; ++i) {
        LO[A[i]] = min(LO[A[i]], i);
        HI[A[i]] = max(HI[A[i]], i);
    }
    
    ConstTree<int, MinQOp<int>> T(A);
    for (int q = 1; q <= Q; ++q) {
        if (HI[q] != -1) {
            if (T.get(LO[q],HI[q]) < q) {
                cout << "NO\n";
                return;
            }
        }
    }
    
    cout << "YES\n";
    cout << A;
}
};
