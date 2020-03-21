#include "../l/lib.h"

class AAsSimpleAsOneAndTwo {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            string S; cin >> S;
            int N = S.size();
            vector<int> Rem;
            for (int i = 0; i < N-2; ++i) {
                if (S[i] == 't' && S[i+1] == 'w' && S[i+2] == 'o') {
                    if (i+3 == N || S[i+3] != 'o') {
                        Rem.push_back(i + 3);
                        i += 2;
                    } else {
                        Rem.push_back(i + 2);
                        i += 1;
                    }
                } else if (S[i] == 'o' && S[i+1] == 'n' && S[i+2] == 'e') {
                    Rem.push_back(i+2);
                    i += 2;
                }
            }
            cout << Rem.size() << '\n' << Rem;
        }
    }
};
