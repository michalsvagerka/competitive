#include "../../../l/lib.h"

class BWorldCup {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> T(N);
        pii ans = {1000000006, -1};
        for (int i = 0; i < N; ++i) {
            int rounds = (A[i] - i + N - 1)/N;
            int time = rounds * N + i + 1;
            ans = min(ans, {time, i});
        }
        cout << ans.y+1 << endl;
    }
};
