#include "../../../l/lib.h"
// #include "../l/mod.h"

class linkcuttree {
public:
    void solve(istream& cin, ostream& cout) {
        ll L,R; int K;
        cin >> L >> R >> K;
        vector<ll> Ans;
        ll T = 1;
        while (T <= R/K) {
            if (in(L,T,R+1)) Ans.push_back(T);
            T *= K;
        }
        if (in(L,T,R+1)) Ans.push_back(T);



        if (Ans.empty()) {
            cout << "-1\n";
        } else {
            cout << Ans;
        }
    }
};
