#include "../../../l/lib.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> B(2*N); cin >> B;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int j;
        for (j = 1; j < B.size(); ++j) {
            if (B[j] == B[0]) break;
        }
        ans += j-1;
        B.erase(B.begin()+j);
        B.erase(B.begin());
    }
    cout << ans << endl;
}
};
