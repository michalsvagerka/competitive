#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int M = 23;

class Subgraphs {
public:
    vector<string> findGroups(int K) {
        vector2<bool> A(2*M,2*M,false);
        for (int i = 0; i < M; ++i) {
            for (int j = i+1; j < M; ++j) A[i][j] = A[j][i] = true;
            for (int j = 2*M-i; j < 2*M; ++j) A[i][j] = A[j][i] = true;
        }

        vector<string> Q(2*M + 1 + K*(K-1)/2);
        for (int l = 0; l <= K*(K-1)/2; ++l) {
            Q[2*M+l] = string(2*M, 'N');
            int q = 1;
            while (q*(q+1)/2 <= l) ++q;
            for (int j = 0; j < q; ++j) Q[2*M+l][j] = 'Y';
            for (int j = M; j < M+(K-q)-1; ++j) Q[2*M+l][j] = 'Y';
            if (q != K) Q[2*M+l][2*M - q + (l - q*(q-1)/2)] = 'Y';
        }

        for (int i = 0; i < 2 * M; ++i) {
            Q[i] = string(2*M,'0');
            for (int j = 0; j < 2 * M; ++j) {
                if (A[i][j]) Q[i][j] = '1';
            }
        }

        return Q;
    }


    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        cout << findGroups(K);
    }
};
