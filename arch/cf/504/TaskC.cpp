#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    string S; cin >> S;
    vector<int> Ans, Stack;
    int open = 0;
    for (int i = 0; i < N; ++i) {
        if (S[i] == '(') {
            Stack.push_back(open);
            Ans.push_back(open);
            ++open;
        } else {
            Ans.push_back(Stack.back());
            Stack.pop_back();
        }
    }
    
    for (int i = 0; i < N; ++i) if (Ans[i] < K/2) cout << S[i];
    cout << '\n';
}
};
