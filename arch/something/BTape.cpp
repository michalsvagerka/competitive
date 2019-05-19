#include "../l/lib.h"
// #include "../l/mod.h"

class BTape {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, L; cin >> N >> M >> L;
    vector<int> B(N); cin >> B;
    sort(B.begin(),B.end());
    L -= N;
    vector<int> D(N-1);
    for (int i = 0; i < N - 1; ++i) {
        D[i] = B[i+1] - B[i] - 1;
    }
    sort(D.begin(),D.end());
    int c = N;
    for (int d: D) {
        if (d <= L) {
            L -= d;
            c--;
        }
    }

    cout << c << endl;
}
};
