#include "../l/lib.h"

class aviao {
public:
    void solve(istream& cin, ostream& cout) {
        int R, S, C; cin >> R >> S >> C;
        vector<int> T(C);
        vector<pii> P(C); cin >> P;
        for (int i = 0; i < C; ++i) {
            int y = 0;
            if (P[i].y <= S) {
                y = S + 1 - P[i].y;
            } else {
                y = P[i].y - S;
            }
            int x = P[i].x;
            T[i] = x + y;
        }

        sort(T.begin(),T.end());
        for (int i = 1; i < C; ++i) {
            if (T[i] <= T[i-1]) {
                T[i] = T[i-1] + 1;
            }
        }

        cout << T.back() << endl;
    }
};
