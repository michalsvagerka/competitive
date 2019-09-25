#include "../l/lib.h"
#include "../l/mod.h"

class ClassTreasurer {
public:
    int T = 0;
    void solve(istream& cin, ostream& cout) {
        cout << "Case #" << ++T << ": ";
        int N, K; cin >> N >> K;
        string S; cin >> S;
        reverse(S.begin(),S.end());
        FieldMod ans = 0;
        int up = 0, cur = 0;
        for (char s: S) {
            cur += (s == 'A') - (s == 'B');
            up = max(up, cur);
            if (up - cur > K) {
                ans++;
                cur += 2;
                up = max(up, cur);
            }

            ans *= 2;
        }
        cout << ans << '\n';
    }
};
