#include "../l/lib.h"

class AIlyaAndAColorfulWalk {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> C(N); cin >> C;

        int i = 0;
        while (C[i] == C[N-1]) ++i;

        int j = N-1;
        while (C[0] == C[j]) --j;

        int ans = max(N-1-i, j);
        cout << ans << '\n';
    }
};
