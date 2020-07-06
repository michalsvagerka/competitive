#include "../l/lib.h"

class ARomaji {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        for (int i = 0; i < N; ++i) {
            char c = S[i];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'n') {
                continue;
            } else {
                if (i == N-1) {
                    cout << "NO\n";
                    return;
                }
                char d = S[i+1];
                if (d == 'a' || d == 'e' || d == 'i' || d == 'o' || d == 'u') {
                    continue;
                } else {

                    cout << "NO\n";
                    return;
                }
            }
        }
        cout << "YES\n";
    }
};
