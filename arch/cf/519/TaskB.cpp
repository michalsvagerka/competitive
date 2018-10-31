#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector<int> B(N);
    B[0] = A[0];
    for (int i = 1; i < N; ++i) B[i] = A[i] - A[i-1];
    
    vector<int> Ans;
    for (int k = 1; k <= N; ++k) {
        bool ok = true;
        for (int i = 0; i+k < N; ++i) {
            ok &= B[i+k] == B[i];
        }
        if (ok) Ans.push_back(k);
    }
    cout << Ans.size() << '\n' << Ans;
}
};
