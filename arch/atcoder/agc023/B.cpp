#include "../../../l/lib.h"
// #include "../l/mod.h"

class B {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            bool ok = true;
            for (int j = 0; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    ok &= S[j][k] == S[k][j];
                }
            }
            ans += ok;

            for (string&s:S) rotate(s.begin(),s.begin()+1,s.end());
        }

        cout << ans * N << endl;
    }
};
