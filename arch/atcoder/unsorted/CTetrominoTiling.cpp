#include "../l/lib.h"
// #include "../l/mod.h"

class CTetrominoTiling {
public:
void solve(istream& cin, ostream& cout) {
    ll AI, AO, AT, AJ, AL, AS, AZ;
    cin >> AI >> AO >> AT >> AJ >> AL >> AS >> AZ;
    ll ans = AO;
    ans += 2 * (AL/2) + 2 * (AI/2) + 2 * (AJ/2);
    int s = (AL%2) + (AJ%2) + (AI%2);
    if (s == 3) ans += 3;
    if (s == 2 && min(AL, min(AJ, AI)) != 0) ans += 1;
    cout << ans << '\n';
}
};
