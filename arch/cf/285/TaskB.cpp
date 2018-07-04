#include "../../../l/lib.h"
 #include "../../../l/fenwick.h"
#include "../../../l/avl.h"

class TaskB {
public:
    int N;

    vector<int> order(const vector<int> & X) {
        vector<int> O(N);
        Fenwick<int> F(N, 0);
        for (int i = 0; i < N; ++i) {
            O[i] = X[i] - F.sum(X[i]);
            F.add(X[i], 1);
        }
        return O;
    }
void solve(istream& cin, ostream& cout) {
    cin >> N;
    vector<int> A(N), B(N);
    cin >> A >> B;

    vector<int> O = order(A), P = order(B);
    for (int i = 1; i < N; ++i) {
        if (O[N-i] >= i) {
            O[N-i] -= i;
            O[N-i-1]++;
        }
        O[N-i-1] += P[N-i-1];
    }
    O[0] %= N;

    avl<int,int> T;
    for (int i = 0; i < N; ++i) {
        T.insert(i,i);
    }


    vector<int> Ans(N);
    for (int i = 0; i < N; ++i) {
        Ans[i] = T.select(O[i])->k;
        T.remove(Ans[i]);
    }
    cout << Ans;

}
};
