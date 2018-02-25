#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> B(3*N); cin >> B;
        sort(B.begin(),B.end());
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += B[3*N-2-2*i];
        }
        cout << ans << endl;
    }
};
