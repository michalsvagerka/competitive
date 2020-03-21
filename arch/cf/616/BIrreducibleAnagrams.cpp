#include "../l/lib.h"

class BIrreducibleAnagrams {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int Q; cin >> Q;
        int N = S.size();
        vector2<int> C(26, N+1, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 26; ++j) {
                C[j][i+1] = C[j][i];
            }
            C[S[i]-'a'][i+1]++;
        }

        for (int q = 0; q < Q; ++q) {
            int L, R; cin >> L >> R;
            --L; --R;
            if (L == R) {
                cout << "Yes\n";
            } else if (S[L] != S[R]) {
                cout << "Yes\n";
            } else {
                int cnt = 0;
                for (int i = 0; i < 26; ++i) {
                    cnt += C[i][R+1] != C[i][L];
                }
                if (cnt >= 3) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            }
        }
    }
};
