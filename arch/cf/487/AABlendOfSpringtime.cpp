#include "../../../l/lib.h"

class AABlendOfSpringtime {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        cin >> S;
        int N = S.size();
        for (int i = 0; i < N-2; ++i) {
            if (set<char>{S[i],S[i+1],S[i+2],'.'}.size() == 4) {
                cout << "Yes\n";
                return;
            }
        }
        cout << "No\n";
    }
};
