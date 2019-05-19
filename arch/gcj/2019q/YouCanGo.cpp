#include "../l/lib.h"

class YouCanGo {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            string S; cin >> S;
            for (char&s: S) {
                if (s == 'E') s = 'S';
                else s = 'E';
            }
            cout << "Case #" << t+1 << ": " << S << '\n';
        }

    }
};
