#include "../l/lib.h"

class BHateA {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int C = count(S.begin(),S.end(), 'a');
        int N = S.size();
        if ((N+C) % 2 == 1) {
            cout << ":(\n";
            return;
        }

        int M = (N+C)/2;
        int j = M;
        for (int i = 0; i < M; ++i) {
            if (S[i] != 'a') {
                if (j == N || S[i] != S[j]) {
                    cout << ":(\n";
                    return;
                }

                ++j;
            }
        }

        cout << S.substr(0, M) << endl;

    }
};
