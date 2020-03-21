#include "../l/lib.h"
#include "../l/mod.h"
class ACutAndPaste {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int X; cin >> X;
            string S; cin >> S;
            FieldMod len = S.size();
            for (int i = 0; i < X; ++i) {
                int c = S[i]-'0';
                len += (c-1)*(len-i-1);
                if ((int)S.size() < X && c != 1) {
                    string T = S.substr(i+1, (int)S.size()-i-1);
                    for (int w = 1; w < c; ++w) S += T;
                }
            }
            cout << len << '\n';
        }
    }
};
