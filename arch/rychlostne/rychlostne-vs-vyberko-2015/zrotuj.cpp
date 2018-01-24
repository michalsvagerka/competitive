#include "../l/lib.h"
// #include "../l/mod.h"

class zrotuj {
public:
    bool letter(char c) {
        return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
    }

    bool upper(char c) {
        return (c>='A'&&c<='Z');
    }

    char toupper(char c) {
        return !upper(c) ? c + 'A' - 'a' : c;
    }

    char tolower(char c) {
        return upper(c) ? c + 'a' - 'A' : c;
    }

    void solve(istream& cin, ostream& cout) {
        string S;
        while (getline(cin, S)) {
            ui i = 0, N = S.size();
            while (i < N) {
                while (i < N && !letter(S[i])) ++i;
                int j = i;
                while (j < N && letter(S[j])) ++j;
                ui s = j-i;
                vector<bool> U(s);
                for (int k = 0; k < s; ++k) {
                    U[k] = upper(S[i+k]);
                    S[i+k] = tolower(S[i+k]);
                }
                if (s%2 == 0) {
                    for (int k = 0; k < s/2; ++k) {
                        swap(S[i+k],S[i + s/2 + k]);
                    }
                }  else {
                    for (int k = 0; k < s/2; ++k) {
                        swap(S[i+k],S[i + s - 1 - k]);
                    }
                }
                for (int k = 0; k < s; ++k) if (U[k]) S[i + k] = toupper(S[i + k]);
                i = j + 1;
            }

            cout << S << '\n';
        }
    }
};
