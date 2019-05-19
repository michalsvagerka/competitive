#include "../l/lib.h"
// #include "../l/mod.h"

class BGoodSequences {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    vector<bool> R(1e5+1, false);
    for (int a:A) R[a] = true;
    vector<vector<int>> E(1e5+1);
    E[0].push_back(1);
    for (int i = 2; i <= 1e5; ++i) {
        int l = 0;
        for (int j = i; j <= 1e5; j += i) {
            if (R[j]) {
                E[l].push_back(j);
                l = j;
            }
        }
    }
    vector<int> C(1e5+1, 0);
    for (int i = 0; i <= 1e5; ++i) {
        for (int j : E[i]) {
            C[j] = max(C[j], C[i]+1);
        }
    }
    cout << *max_element(C.begin(),C.end()) << endl;
}
};
