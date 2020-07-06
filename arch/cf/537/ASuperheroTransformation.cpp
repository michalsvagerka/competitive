#include "../l/lib.h"

class ASuperheroTransformation {
public:
    bool vowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    void solve(istream& cin, ostream& cout) {
        string S, T;
        cin >> S >> T;
        int N = S.size();
        int M = T.size();
        if (N != M) {
            cout << "No\n";
        } else {
            for (int i = 0; i < N; ++i) {
                bool a = vowel(S[i]);
                bool b = vowel(T[i]);
                if (a^b) {
                    cout << "No\n";
                    return;
                }
            }
            cout << "Yes\n";
        }
    }
};
