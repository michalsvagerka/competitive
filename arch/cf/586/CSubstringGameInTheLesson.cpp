#include "../l/lib.h"

class CSubstringGameInTheLesson {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        char lo = 'z';
        for (int i = 0; i < N; ++i) {
            if (S[i] > lo) {
                cout << "Ann\n";
            } else {
                cout << "Mike\n";
            }
            lo = min(lo, S[i]);
        }
    }
};
