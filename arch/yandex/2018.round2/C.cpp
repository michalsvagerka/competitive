#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int Mana, N, strikeDamage, strikeCost, iceDamage, iceCost;
        cin >> N >> Mana >> strikeDamage >> strikeCost >> iceDamage >> iceCost;

        vector<int> H(N);
        cin >> H;
        sort(H.begin(),H.end());

        int ans = 0;
        for (int i = 0; i <= Mana/iceCost; ++i) {
            int q = (Mana-iceCost*i)/strikeCost;
            int cur = 0;
            for (int h:H) {
                int n = max(0, (h+strikeDamage-1)/strikeDamage);
                if (n <= q) {
                    q -= n;
                    ++cur;
                }
            }

            ans = max(cur, ans);

            for (int&h:H) h -= iceDamage;
        }
        cout << ans << endl;
    }
};
