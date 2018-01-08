#include "../l/lib.h"
// #include "../l/mod.h"

class fewswaps {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        set<vector<int>> S; S.insert(A);
        for (int k = 0; k < K; ++k) {
            set<vector<int>> R;
            for (auto s: S) {
                for (int i = 0; i < N; ++i) {
                    for (int j = i+1; j < N; ++j) {
                        swap(s[i], s[j]);
                        R.insert(s);
                        swap(s[i], s[j]);
                    }
                }
            }
            swap(R, S);
        }
        cout << S.size() << endl;
    }
};
