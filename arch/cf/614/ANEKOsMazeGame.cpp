#include "../l/lib.h"

class ANEKOsMazeGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector2<bool> A(2, N, false);
        int bad = 0;
        for (int q = 0; q < Q; ++q) {
            int a, b; cin >> a >> b; --a; --b;
            for (int i = max(0, b-1); i <= min(N-1,b+1); ++i) bad -= A[1-a][i]&&A[a][b];
            A[a][b] = !A[a][b];
            for (int i = max(0, b-1); i <= min(N-1,b+1); ++i) bad += A[1-a][i]&&A[a][b];
            cout << (bad?"No":"Yes") << '\n';
        }
    }
};
