#include "../l/lib.h"
// #include "../l/mod.h"

vector<pii> D{{1,2},{-1,-2},{1,-2},{-1,2},{2,1},{2,-1},{-2,1},{-2,-1}};
class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    int W = 550;
    vector2<bool> G(W, W, false);
    int L = N/2+1;

    int M = N;
    for (int i = 0; i < L; ++i) {
        if (M-- > 0) {
            G[i][L/2] = true;
        }
    }

    for (int i = 0; i < L; ++i) {
        if (i != L/2 && M-- > 0) {
             G[L/2][i] = true;
        }
    }
}
};
