#include "../../../l/lib.h"

class DPolycarpAndDiv3 {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        vector2<int> D(N+1, 3, 0);
        for (int i = 0; i < N; ++i) {
            int a = (S[i]-'0')%3;
            for (int j = 0; j < 3; ++j) {
                D[i+1][(j+a)%3] = max(D[i+1][(j+a)%3], D[i][j]);
                D[i+1][a] = max(D[i+1][a], D[i][j] + (j==0));
            }
        }

        cout << max(D[N][0] + 1, max(D[N][1], D[N][2]))-1 << '\n';
    }
};
