#include "../../../l/lib.h"
// #include "../l/mod.h"

class shakespeare {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        vector<pii> V;
        int N = S.size();
        for (int j = N-1; j >= 0; --j) {
            if (S[j] == '1') {
                int i = N-j-1;
                if (!V.empty() && V.back().y == i) {
                    V.back().y++;
                } else if (!V.empty() && V.back().y == i-1) {
                    V.back().x = 0;
                    V.push_back({1,i+1});
                } else {
                    V.push_back({1,i});
                }
            }
        }

        cout << V.size() << '\n';
        for (pii&v:V) {
            cout << "-+"[v.x] << "2^" << v.y << '\n';
        }
    }
};
