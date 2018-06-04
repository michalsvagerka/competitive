#include "../../../l/lib.h"
// #include "../l/mod.h"

class errorcorrect {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S,T; cin >> S >> T;
        vector2<int> R(26,26,0);
        int ham = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] != T[i]) {
                ++ham;
                R[S[i]-'a'][T[i]-'a'] = i+1;
            }
        }

        for (int j = 0; j < 26; ++j) {
            for (int k = 0; k < 26; ++k) {
                if (R[j][k] && R[k][j]) {
                    cout << ham-2 << '\n' << R[j][k] << ' ' << R[k][j] << '\n';
                    return;
                }
            }
        }

        for (int j = 0; j < 26; ++j) {
            for (int k = 0; k < 26; ++k) {
                for (int l = 0; l < 26; ++l) {
                    if (R[j][k] && R[k][l]) {
                        cout << ham - 1 << '\n' << R[j][k] << ' ' << R[k][l] << '\n';
                        return;
                    }
                }
            }
        }

        cout << ham << "\n-1 -1\n";
    }
};
