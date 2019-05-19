#include "../l/lib.h"

class BSashaAndOneMoreName {
public:
    bool is_palin(string S) {
        int N = S.size();
        for (int i = 0; i < N / 2; ++i) {
            if (S[i] != S[N-i-1]) return false;
        }
        return true;
    }

    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        vector<int> C(26, 0);
        int N = S.size();
        for (char c: S) C[c-'a']++;
        int m = *max_element(C.begin(),C.end());
        if (m >= N-1) {
            cout << "Impossible\n";
        } else {
            for (int i = 1; i <= N-1; ++i) {
                string T = S.substr(i) + S.substr(0, i);
                if (is_palin(T) && T != S) {
                    cout << 1 << '\n';
                    return;
                }
            }
            cout << 2 << '\n';
        }
    }
};
