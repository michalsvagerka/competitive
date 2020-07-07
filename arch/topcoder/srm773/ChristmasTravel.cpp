#include "../../../l/lib.h"

class ChristmasTravel {
public:
    vector <string> plan(int N, int A) {
        vector<string> S(N, string(N, '-'));
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if ((j&1<<i) != (k&1<<i)) {
                        S[j][k] = (char)('A'+i);
                    }
                }
            }
        }

        map<char,int> C;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                C[S[i][j]]++;
            }
        }
        
        if (C[(char)('A' + A)]) {
            return {};
        }
        
        map<char, int> D;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if (D[S[i][j]]) {
                    for (int k = 0; k < A; ++k) {
                        if (C[(char)('A'+k)] == 0 && D[(char)('A'+k)] == 0) {
                            S[i][j] = S[j][i] = (char)('A'+k);
                        }
                    }
                }
                
                D[S[i][j]]++;
            }
        }

        for (int i = 0; i < A; ++i) {
            if (D[(char)('A'+i)] == 0) return {};
        }
        
        return S;
    }

    void solve(istream& cin, ostream& cout) {
        cout << plan(3, 1) << '\n';
        cout << plan(3, 3) << '\n';
        cout << plan(5,3) << '\n';
        cout << plan(1, 1) << '\n';
        cout << plan(6, 5) << '\n';


    }
};
