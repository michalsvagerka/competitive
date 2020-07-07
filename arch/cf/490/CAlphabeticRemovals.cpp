#include "../../../l/lib.h"

class CAlphabeticRemovals {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string S; cin >> S;
        vector<vector<int>> P(26);
        for (int i = 0; i < N; ++i) {
            P[S[i]-'a'].push_back(i);
        }
        
        vector<bool> U(N, true);
        for (int i = 0; i < 26; ++i) {
            for (int j: P[i]) {
                if (K) {
                    U[j] = false;
                    --K;
                }
            }
        }
        string T;
        for (int i = 0; i < N; ++i) {
            if (U[i]) T += S[i];
        }
        cout << T << endl;
    }
};
