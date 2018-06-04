#include "../../../l/lib.h"
// #include "../l/mod.h"

class playingwithpaper {
public:
    void solve(istream& cin, ostream& cout) {
        ll A, B; cin >> A >> B;
        ll ans = 0;
        if (A < B) swap(A,B);
        while (B!=0) {
            ans += A/B;
            A = A%B;
            swap(A,B);
        }
        cout << ans << '\n';
    }
};
