#include "../../../l/lib.h"
#include "../../../l/mod.h"

class MagicNumberThree {
public:
    int countSubsequences(string s) {
        int N = s.size();
        vector2<FieldMod> D(N+1, 3, 0);
        D[0][0] = 1;
        for (int i = 0; i < N; ++i) {
            int d = s[i]-'0';
            for (int j = 0; j < 3; ++j) {
                D[i+1][j] += D[i][j];
                D[i+1][(j+d)%3] += D[i][j];
            }
        }

        return ui(D[N][0] - 1);
    }

    void solve(istream& cin, ostream& cout) {
        string s; cin >> s;
        cout << countSubsequences(s) << '\n';
    }
};
