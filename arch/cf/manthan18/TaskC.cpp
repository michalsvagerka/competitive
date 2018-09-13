#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    string A, B; cin >> A >> B;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] != B[i]) {
            if (i != N-1 && A[i+1] == B[i] && A[i] == B[i+1]) {
                ++i;
            }
            ++ans;
        }
    }
    cout << ans << endl;
}
};
