#include "../l/lib.h"
// #include "../l/mod.h"

class DMagicStones {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> C(N), T(N); cin >> C >> T;
    vector<int> A(N-1), B(N-1);
    for (int i = 0; i < N - 1; ++i) {
        A[i] = C[i+1] - C[i];
        B[i] = T[i+1] - T[i];
    }
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());

    if (A == B && C[0] == T[0] && C[N-1] == T[N-1]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
};
