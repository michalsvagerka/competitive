#include "../l/lib.h"

class reconstructn {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        vector2<int> D(N+1, 10, 10);
        for (int i = 0; i < 10; ++i) {
            D[N][i] = 0;
        }

        for (int i = N; i > 0; --i) {
            for (int j = 0; j < 10; ++j) {
                if (D[i][j] == 10) continue;
                for (int k = 0; k < 10; ++k) {
                    bool ok = false;
                    switch (S[i-1]) {
                        case '=': ok = k==j; break;
                        case '<': ok = k<j; break;
                        case '>': ok = k>j; break;
                        case '!': ok = k!=j; break;
                    }
                    if (ok) {
                        D[i-1][k] = min(D[i-1][k], j);
                    }
                }
            }
        }
        
        for (int i = 1; i < 10; ++i) {
            if (D[0][i] != 10) {
                cout << i;
                for (int j = 0; j < N; ++j) {
                    i = D[j][i];
                    cout << i;
                }
                cout << '\n';
                return;
            }
        }

        cout << "neexistuje\n";
    }
};
