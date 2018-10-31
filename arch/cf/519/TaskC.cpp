#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int N = S.size();
    vector<int> Ans(N, 0);
    for (int i = 1; i < N; ++i) {
        string T = S;
        reverse(T.begin(),T.begin()+i);
        reverse(T.begin(),T.begin()+i+1);
        if (T < S) {
            Ans[i-1] = 1 - Ans[i-1];
            Ans[i] = 1;
            S = T;
        }
    }
    
    cout << Ans;
}
};
