#include "../l/lib.h"

class strings {
public:
    int palin(string S) {
        int N = S.size();
        vector2<bool> P(N+1, N+1, false);
        for (int i = 0; i < N; ++i) {
            P[i][i] = true;
        }
        for (int i = 0; i < N - 1; ++i) {
            if (S[i] == S[i+1]) P[i][i+1] = true;
        }
        for (int l = 3; l <= N; ++l) {
            for (int i = 0; i + l <= N; ++i) {
                int j = i + l - 1;
                P[i][j] = P[i+1][j-1] && (S[i] == S[j]);
            }
        }

        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cnt += P[i][j];
            }
        }
        return cnt;

    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int K; cin >> K;
            int L = K;
            string S;
            while (K != 0) {
                int j = 1;
                while ((j+2) * (j+1) / 2 <= K) j++;
                S += string(j, 'A');
                K -= j*(j+1)/2;
                if (K) {
                    S += 'B';
                    --K;
                }
                if (K) {
                    S += 'C';
                    --K;
                }
            }

            cout << "Case #" << t+1 << ": " << S << endl;
        }
    }
};
