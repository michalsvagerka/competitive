#include "../../../l/lib.h"

class CAMistOfFlorescence {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, C, D; cin >> A >> B >> C >> D;
        vector<string> Ans(50, string(50, '-'));
        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 50; ++j) {
                Ans[i][j] = "AB"[j>=25];
            }
        }

        for (int i = 0; i < A-1; ++i) {
            Ans[25+2*(i/10)+1][25+2*(i%10)+1] = 'A';
        }

        for (int i = 0; i < B-1; ++i) {
            Ans[25+2*(i/10)+1][2*(i%10)+1] = 'B';
        }

        for (int i = 0; i < C; ++i) {
            Ans[2*(i/10)+1][2*(i%10)+1] = 'C';
        }

        for (int i = 0; i < D; ++i) {
            Ans[2*(i/10)+1][25+2*(i%10)+1] = 'D';
        }

        cout << "50 50\n";
        for (auto ans: Ans) cout << ans << '\n';
    }
};
