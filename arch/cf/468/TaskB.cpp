#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        vector<vector<string>> T(26);
        for (int i = 0; i < S.size(); ++i) {
            T[S[0]-'a'].push_back(S);
            rotate(S.begin(),S.begin()+1,S.end());
        }

        int R = 0;
        for (int i = 0; i < 26; ++i) {
            int B = 0;
            for (int j = 1; j < S.size(); ++j) {
                vector<int> C(26, 0);
                for (auto&t:T[i]) {
                    C[t[j]-'a']++;
                }
                int Q = 0;
                for (int k = 0; k < 26; ++k) {
                    Q += C[k] == 1;
                }
                B = max(B, Q);
            }
            R += B;
        }
        cout << fixed << setprecision(15) << double(R)/S.size() << endl;
    }
};
