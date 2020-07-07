#include "../../../l/lib.h"
#include "../../../l/consttree.h"

class DBalancedPlaylist {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int lo = *min_element(A.begin(),A.end());
        int hi = *max_element(A.begin(),A.end());
        if (2*lo >= hi) {
            vector<int> Ans(N, -1);
            cout << Ans;
            return;
        }
        
        vector<int> B(3*N+1);
        for (int i = 0; i < N; ++i) {
            B[i] = B[i+N] = B[i+2*N] = A[i];
        }
        B[3*N] = 0;

        
        ConstTree<int, MinQOp<int>> CT(B);
        vector<int> Stop(3*N+1);
        for (int i = 0; i < N; ++i) {
            Stop[i] = bsl(i, 3*N, [&](int j) { return 2 * CT.get(i, j) < A[i]; });
            Stop[i+N] = Stop[i] + N;
            Stop[i+2*N] = Stop[i] + 2*N;
        }

        Stop[3*N] = 3*N;
        for (int i = 0; i <= 3*N; ++i) {
            if (Stop[i] >= 3*N) Stop[i] = 3*N+1;
        }
        
        ConstTree<int, MinQOp<int>> Next(Stop);
        vector<int> End(N);
        for (int i = 0; i < N; ++i) {
            End[i] = bsh(i, 3*N, [&](int j) { return Next.get(i, j) > j; });
        }

        for (int i = 0; i < N; ++i) {
            End[i] = End[i] - i + 1;
        }
        cout << End;
    }
};
