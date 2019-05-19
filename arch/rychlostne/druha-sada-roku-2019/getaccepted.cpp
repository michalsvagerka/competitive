#include "../l/lib.h"

class getaccepted {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        getline(cin, S);
        int N = S.size();
        int cnt = 0;
        for (int i = 0; i < N - 5; ++i) {
            cnt += S.substr(i, 5) == " not ";
        }
        if (cnt%2) cout << "False.\n"; else cout << "True.\n";
    }
};
