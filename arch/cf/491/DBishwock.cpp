#include "../../../l/lib.h"

class DBishwock {
public:
    void solve(istream& cin, ostream& cout) {
        vector<string> S(2); cin >> S;
        int N = S[0].size();
        vector2<int> D(N+1, 4, -10000);
        D[0][3] = 0;
        for (int i = 0; i < N; ++i) {
            int a = (S[0][i] == 'X') | (S[1][i] == 'X')<<1;
            for (int j = 0; j < 4; ++j) {
                int b = (j<<2) | a;
                if (__builtin_popcount(b) == 1) {
                    D[i+1][3] = max(D[i+1][3], D[i][j] + 1);
                }
                if (b == 0) {
                    D[i+1][1] = max(D[i+1][1], D[i][j] + 1);
                    D[i+1][2] = max(D[i+1][2], D[i][j] + 1);
                }
                D[i+1][a] = max(D[i+1][a], D[i][j]);
            }
        }

        cout << *max_element(D[N].begin(),D[N].end()) << '\n';
    }
};
