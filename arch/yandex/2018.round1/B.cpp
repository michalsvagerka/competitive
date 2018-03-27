#include <numeric>
#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        vector<int> V(N);
        for (int i = 0; i < N; ++i) {
                V[i] = S[i]-'0';
        };
        vector<int> Q(10);
        iota(Q.begin(),Q.end(),0);
        int ans = 0;
        do {
            int m = 0;
            for (int i = 0; i < N; ++i) {
                if (Q[V[i]] == m) ++m;
            }
            if (m == 10) ++ans;

        } while (next_permutation(Q.begin(),Q.end()));

        cout << ans << endl;
    }
};
