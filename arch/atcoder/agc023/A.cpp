#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<ll, int> C;
        C[0] = 1;
        ll ans = 0, cur = 0;
        for (int a:A) {
            cur += a;
            ans += C[cur];
            C[cur] += 1;
        }
        cout << ans << endl;
    }
};
