#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    int M = (1<<K) - 1;
    vector<int> A(N); cin >> A;

    map<int, int> C;
    C[0] = 1;

    ll ans = 0, cur = 0;
    for (int i = 0; i < N; ++i) {
        cur ^= A[i];
        int a = cur, b = M ^ cur;
        if (C[a] > C[b]) {
            ans += C[b];
            C[b]++;
            cur = b;
        } else {
            ans += C[a];
            C[a]++;
        }
    }
    
    cout << ll(N) * ll(N+1) / 2 - ans << endl;
}
};
