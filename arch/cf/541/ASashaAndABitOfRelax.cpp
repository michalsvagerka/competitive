#include "../l/lib.h"

class ASashaAndABitOfRelax {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<int, int> V[2];
        V[0][0] = 1;
        int c = 0;
        ll ans = 0;
        for (int i = 1; i <= N; ++i) {
            c ^= A[i-1];
            ans += V[i%2][c];
            V[i%2][c]++;
        }
        cout << ans << endl;
    }
};
