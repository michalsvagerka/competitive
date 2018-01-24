#include "../l/lib.h"
// #include "../l/mod.h"

class fencerepair {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        ll ans = 0;
        minheap<ui> S;
        for (ui i = 0; i < N; ++i) {
            int a; cin >> a; S.push(a);
        }

        while (S.size() != 1) {
            int a = S.top(); S.pop();
            int b = S.top(); S.pop();
            S.push(a+b);
            ans += a+b;
        }
        cout << ans << endl;
    }
};
