#include "../../../l/lib.h"

class ASonyaAndHotels {
public:
    void solve(istream& cin, ostream& cout) {
        int N, D; cin >> N >> D;
        vector<int> X(N); cin >> X;
        int ans = 2;
        for (int i = 0; i < N-1; ++i) {
            ans += X[i+1]-X[i]>=2*D;
            ans += X[i+1]-X[i]>2*D;
        }
        cout << ans << '\n';
    }
};
