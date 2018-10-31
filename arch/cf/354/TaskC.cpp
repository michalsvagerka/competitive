#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    string S; cin >> S;
    vector<int> A{-1}, B{-1};
    for (int i = 0; i < N; ++i) {
        if (S[i] == 'a') A.push_back(i);
        else B.push_back(i);
    }
    A.push_back(N);
    B.push_back(N);
    
    if (min(A.size(), B.size()) <= K+2) {
        cout << N << endl;
    } else {
        int ans = 0;
        for (int a = 0; a + K + 1 < A.size(); ++a) {
            ans = max(ans, A[a+K+1] - A[a] - 1);
        }

        for (int b = 0; b + K + 1 < B.size(); ++b) {
            ans = max(ans, B[b+K+1] - B[b] - 1);
        }
        
        cout << ans << endl;
    }
    
    
    
}
};
