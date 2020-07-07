#include "../../../l/lib.h"

class ALongBeautifulInteger {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string S; cin >> S;
        string T = S.substr(0, K);
        
        string U = T;
        int M = K-1;
        while (M >= 0 && U[M] == '9') {
            U[M] = '0';
            --M;
        }

        if (M == -1) {
            U = "1" + U;
            U.resize(K);
            while (U.size() <= N) U += U;
            U.resize(N+1);
        } else {
            U[M]++;

            while (U.size() < N) U += U;
            U.resize(N);
        }


        while (T.size() < N) T += T;
        T.resize(N);
        
        cout << N << endl;
        for (int i = 0; i < N; ++i) {
            if (S[i] < T[i]) {
                cout << T << endl;
                return;
            }
            if (S[i] > T[i]) {
                cout << U << endl;
                return;
            }
        }
        
        cout << T << endl;
    }
};
