#include "../l/lib.h"


class Expogo {
public:
    string W = string(100, 'X');

    string solve(int X, int Y, const string&T) {
        if (X == 0 && Y == 0) return T;
        else if (T.length() > 40) return W;
        else if (abs(X%2) == abs(Y%2)) return W;
        else if (X%2) {
            string A = solve((X-1)/2,Y/2, T+"E");
            string B = solve((X+1)/2,Y/2, T+"W");
            if (A.size() < B.size()) return A;
            else return B;
        } else {
            string A = solve(X/2,(Y-1)/2, T+"N");
            string B = solve(X/2,(Y+1)/2, T+"S");
            if (A.size() < B.size()) return A;
            else return B;
        }
    }


    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int X, Y; cin >> X >> Y;
            string ans = solve(X, Y, "");
            cout << "Case #" << t+1 << ": " << (ans == W ? "IMPOSSIBLE" : ans) << '\n';
        }
    }
};
