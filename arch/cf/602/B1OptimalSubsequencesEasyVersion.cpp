#include "../l/lib.h"
#include "../l/avl.h"

class B1OptimalSubsequencesEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int M; cin >> M;
        vector<vector<pii>> Q(N);
        for (int i = 0; i < M; ++i) {
            int K, Pos; cin >> K >> Pos;
            Q[K-1].push_back({Pos, i});
        }
        vector<pii> Val(N);
        for (int i = 0; i < N; ++i) {
            Val[i] = {-A[i],i};
        }
        sort(Val.begin(),Val.end());
    
        vector<int> Ans(M);
        avl<int, int> T;
        for (int i = 0; i < N; ++i) {
            T.insert(Val[i].y, 1);
            for (pii q: Q[i]) {
                Ans[q.y] = A[T.select(q.x-1)->k];
            }
        }
        for (int a:Ans) {
            cout << a << '\n';
        }
    }
};
