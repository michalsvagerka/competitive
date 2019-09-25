#include "../l/lib.h"

class AKenkenRace {
public:
    void solve(istream& cin, ostream& cout) {
        int N, A, B, C, D;
        cin >> N >> A >> B >> C >> D;
        --A; --B; --C; --D;
        string S; cin >> S;
        vector<int> T, U;
        for (int i = A; i < C; ++i) {
            if (S[i] == '#' && S[i+1] == '#') {
                cout << "No\n";
                return;
            }
        }
        for (int i = B; i < D; ++i) {
            if (S[i] == '#' && S[i+1] == '#') {
                cout << "No\n";
                return;
            }
        }

        if (C > D) {
            bool ok = false;
            for (int i = B; i <= D; ++i) {
                if (S[i-1] == '.' && S[i] == '.' && S[i+1] == '.') {
                    ok = true;
                }
            }
            if (!ok) {
                cout << "No\n";
                return;
            }
        }
        
        cout << "Yes\n";
    }
};
