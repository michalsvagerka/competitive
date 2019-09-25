#include "../l/lib.h"

class ACards {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        int one = count(S.begin(),S.end(),'n');
        int zero = count(S.begin(),S.end(),'z');
        
        vector<int> ans(one, 1);
        for (int i = 0; i < zero; ++i) {
            ans.push_back(0);
        }
        cout << ans;
    }
};
