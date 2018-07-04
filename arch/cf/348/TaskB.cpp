#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, Q; cin >> N >> Q;
    int O = 0, T = 1;
    for (int q = 0; q < Q; ++q) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            O = (O+N+x)%N;
            T = (T+N+x)%N;
        } else {
            O ^= 1;
            T ^= 1;
        }
    }

    vector<int> Ans(N);
    for (int i = 0; i < N; i+=2) {
        Ans[(O+i)%N] = 1+i;
        Ans[(T+i)%N] = 2+i;
    }
    cout << Ans;
}
};
