#include "../l/lib.h"
#include "../l/fenwick.h"

class kopec {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<vector<int>> I(100001);
        Fenwick<int> C(N, 0);
        for (int i = 0; i < N; ++i) C.add(i, 1);
        for (int i = 0; i < N; ++i) I[A[i]].push_back(i);

        ll ans = 0;
        int cur = N;
        for (int i = 1; i <= 100000; ++i) {
            for (int j : I[i]) C.add(j, -1);
            cur -= I[i].size();

            for (int j: I[i]) {
                int x = C.sum(j);
                ans += min(x, cur - x);
            }
        }
        cout << ans << endl;
    }
};
