#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N,M; cin >> N >> M;
    vector<string> S(N); cin >> S;
    int x1 = 1000, y1 = 1000;
    int x2 = -1, y2 = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (S[i][j] == 'B') {
                x1 = min(x1, i);
                x2 = max(x2, i);
                y1 = min(y1, j);
                y2 = max(y2, j);
            }
        }
    }

    cout << 1+(x1+x2)/2 << ' ' << 1+(y1+y2)/2 << endl;
}
};
