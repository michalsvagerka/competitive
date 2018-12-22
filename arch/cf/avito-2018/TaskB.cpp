#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector<int> B(N), R(N, 0), C(N);
    int j = 1;
    for (int i = 0; i < N; ++i) {
        if (R[A[i]] == 0) {
            R[A[i]] = N - A[i];
            C[A[i]] = j++;
        }
        
        B[i] = C[A[i]];
        R[A[i]]--;
    }
    
    if (count(R.begin(),R.end(),0) == N) {
        cout << "Possible\n" << B;
    } else {
        cout << "Impossible\n";
    }
}
};
