#include "../l/lib.h"
// #include "../l/mod.h"

class DArraysAndPalindrome {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<int> A(M), B;
    cin >> A;
    int s = 0;
    for (int a:A) s += a%2;
    if (s >= 3) {
        cout << "Impossible\n";
        return;
    }

    bool f = true;
    for (int i = 0; i < M; ++i) {
        if (A[i]%2) {
            if (f) { f = false; swap(A[i],A[0]); }
            else { swap(A[i], A[M-1]); }
        }
    }

    if (A[0] != 1) B.push_back(A[0]-1);
    for (int i = 1; i < M-1; ++i) {
        B.push_back(A[i]);
    }
    B.push_back((M!=1)*A[M-1]+1);

    cout << A << B.size() << '\n' << B;
}
};
