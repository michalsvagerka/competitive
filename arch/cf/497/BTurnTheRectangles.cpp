#include "../l/lib.h"

class BTurnTheRectangles {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> R(N, 2); cin >> R;
        vector2<bool> D(N, 2, false);
        D[0][0] = D[0][1] = true;
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (D[i-1][j] && R[i-1][j] >= R[i][k]) D[i][k] = true;
                }
            }
        }

        if (D[N-1][0] || D[N-1][1]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
