#include "../l/lib.h"
// #include "../l/mod.h"

class BTournament {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N, -1), C(N, 0), Q, D(N, 0);
    vector<vector<int>> E(N);
    for (int i = 1; i < N; ++i) {
        cin >> A[i];
        C[--A[i]]++;
    }

    for (int i = 0; i < N; ++i) {
        if (C[i] == 0) Q.push_back(i);
    }

    for (int i = 0; i < N; ++i) {
        int q = Q[i];
        sort(E[q].begin(), E[q].end());
        reverse(E[q].begin(), E[q].end());
        D[q] = 0;
        for (int j = 0; j < E[q].size(); ++j) {
            D[q] = max(D[q], E[q][j] + j + 1);
        }
        if (A[q] != -1) {
            E[A[q]].push_back(D[q]);
            if (!--C[A[q]]) Q.push_back(A[q]);
        }
    }
    
    cout << D[0] << '\n';
}
};
