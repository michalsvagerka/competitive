#include "../../../l/lib.h"
#include "../../../l/runtimemod.h"

class E {
public:
    int destroy(vector<int> R) {
        if (R.size() == 0) return 1;
        int ans = 0;
        for (int i = 0; i < R.size(); ++i) {
            if (i == R.size()-1 || R[i] > R[i+1]) {
                vector<int> S = R;
                S.erase(S.begin()+i);
                ans += destroy(S);
            }
        }
        return ans;
    }

    int gen(int i, int N, int K, vector<int> &S) {
        if (i == N) {
            return destroy(S);
        } else {
            int ans = 0;
            for (int j = 0; j < K; ++j) {
                S.push_back(j);
                ans += gen(i+1, N, K, S);
                S.pop_back();
            }
            return ans;
        }
    }



    void solve(istream& cin, ostream& cout) {
        ui N,K,M;
        cin >> N >> K >> M;

        vector2<RField> C(N+1,N+1,RField{0,M});
        for (int i = 0; i <= N; ++i) {
            C[i][0] = C[i][i] = RField{1,M};
            for (int j = 1; j < i; ++j) {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
            }
        }

        vector2<RField> D(N+2, K+1, RField{0,M});
        vector2<RField> S(N+2, K+1, RField{0,M});
        for (int x = 0; x <= K; ++x) {
            D[0][x] = D[1][x] = RField{1,M};
            S[0][x] = S[1][x] = RField{K+1-x,M};
        }

        for (int n = 2; n <= N+1; ++n) {
            for (int j = 0; j < K; ++j) {
                for (int k = 1; k <= n; ++k) {
                    D[n][j] += D[n-k][j] * C[n-2][k-1] * S[k][j+1];
                }
            }

            S[n][K] = D[n][K];
            for (int i = K; i > 0; --i) S[n][i-1] = S[n][i] + D[n][i-1];
        }

        cout << D[N+1][0] << '\n';
    }
};
