#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    
    int a, b;
    for (int i = 0; i < N; ++i) {
        if (A[i] == 1) a = i;
        if (A[i] == N) b = i;
    }

    cout << max(max(a, b), N - min(a,b) - 1) << endl;

}
};
