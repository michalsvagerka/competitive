#include "../../../l/lib.h"

class countdownnum2 {
public:
    void solve(istream& cin, ostream& cout) {
        vector<int> C(2000); cin >> C;
        int T; cin >> T;
        sort(C.begin(),C.end());
        vector<int> Ones, Other;
        for (int i = 0; i < 2000; ++i) {
            if (i != 1999 && C[i+1] == C[i]) {
                Ones.push_back(C[i]);
                i++;
            } else {
                Other.push_back(C[i]);
            }
        }

        if (T <= Ones.size()) {
            cout << T << "\n";
            for (int i = 0; i < T; ++i) {
                cout << Ones[i] << ' ' << Ones[i] << " / ";
                if (i != 0) cout << "+ ";
            }
            cout << endl;
            return;
        }

        for (int o : Other) {
            if (abs(o-T) <= Ones.size()) {
                cout << T << '\n' << o;
                for (int i = 0; i < abs(o-T); ++i) {
                    cout << ' ' << Ones[i] << ' ' << Ones[i] << " /";
                    if (o < T) {
                        cout << " +";
                    } else if (o > T) {
                        cout << " -";
                    }
                }
                return;
            }
        }
    }
};
