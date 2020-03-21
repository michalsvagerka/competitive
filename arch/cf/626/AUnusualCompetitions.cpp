#include "../l/lib.h"

class AUnusualCompetitions {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        int op = count(S.begin(),S.end(),'(');
        if (2*op != N) {
            cout << -1 << endl;
            return;
        }

        int bal = 0;
        int below = 0;
        int ans = 0;
        for (char s: S) {
            bal += (s == '(') - (s == ')');
            if (bal == 0) {
                ans += below + (below>0);
                below = 0;
            } else if (bal < 0) {
                below++;
            }
        }

        cout << ans << '\n';
    }
};
