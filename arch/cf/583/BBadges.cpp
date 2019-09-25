#include "../l/lib.h"

class BBadges {
public:
    void solve(istream& cin, ostream& cout) {
        int B, G; cin >> B >> G;
        int N; cin >> N;
        int ans = 0;
        for (int b = 0; b <= B; ++b) {
            for (int g = 0; g <= G; ++g) {
                if (b + g == N) ans++;
            }
        }
        cout << ans << endl;
    }
};
