#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> L(N), R(N);
    cin >> L >> R;
    map<int, vector<int>> S;
    for (int i = 0; i < N; ++i) {
        S[{L[i]+R[i]}].push_back(i);
    }

    int X = S.size();
    vector<int> A(N);
    for (auto &s:S) {
        for (auto i: s.y) A[i] = X;
        --X;
    }

    for (int i = 0; i < N; ++i) {
        int l = 0, r = 0;
        for (int j = 0; j < i; ++j) {
            l += A[j] > A[i];
        }

        for (int j = i+1; j < N; ++j) {
            r += A[j] > A[i];
        }
        
        if (l != L[i] || r != R[i]) {
            cout << "NO\n";
            return;
        }
    }
    
    cout << "YES\n";
    cout << A;
}
};
