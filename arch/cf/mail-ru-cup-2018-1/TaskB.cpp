#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N);
    cin >> A;
    
    int T = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] > T) {
            cout << i+1 << endl;
            return;
        } else if (A[i] == T) {
            T++;
        }
    }
    
    cout << -1 << endl;
}
};
