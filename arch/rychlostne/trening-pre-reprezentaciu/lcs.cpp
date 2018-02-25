#include "../../../l/lib.h"
// #include "../l/mod.h"

class lcs {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector<int> A(N), B(M); cin >> A >> B;
        set<int> Q(A.begin(),A.end());
        if (Q.size() < N) {
            swap(A,B);
            swap(M,N);
        }

        map<int, int> Z;
        for (int i = 0; i < N; ++i) {
            Z[A[i]] = i+1;
        }
        for (int i = 0; i < M; ++i) {
            B[i] = Z[B[i]];
        }

        vector<int> L(M+1, N+1);
        L[0] = 0;
        for (auto b:B) *lower_bound(L.begin(),L.end(),b) = b;
        cout << distance(L.begin(),lower_bound(L.begin(),L.end(),N+1))-1 << endl;
    }
};
