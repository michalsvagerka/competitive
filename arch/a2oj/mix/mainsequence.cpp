#include "../../../l/lib.h"
// #include "../l/mod.h"

class mainsequence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N); cin >> P;
        int T; cin >> T;
        for (int i = 0; i < T; ++i) {
            int x; cin >> x; --x;
            P[x] = -P[x];
        }

        vector<int> Z;
        for (int i = N-1; i >= 0; --i) {
            if (P[i] < 0) Z.push_back(P[i]);
            else if (!Z.empty() && Z.back() + P[i] == 0) Z.pop_back();
            else { Z.push_back(P[i] = -P[i]); }
        }

        if (!Z.empty()) {
            cout << "NO\n";
            return;
        }


        cout << "YES\n";
        cout << P;
    }
};
