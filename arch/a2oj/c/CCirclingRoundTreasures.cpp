#include "../l/lib.h"

class CCirclingRoundTreasures {
public:
    void solve(istream& cin, ostream& cout) {
        ui N, M; cin >> N >> M;
        vector<string> A(N); cin >> A;
        pii S;
        vector2<int> I(N, M, 0);
        int b = 0, t = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (A[i][j] == 'B') {
                    ++b;
                } else if (A[i][j] == 'S') {
                    S = {i,j};
                    A[i][j] = '.';
                } else if (A[i][j] >= '1' && A[i][j] <= '8') {
                    ++t;
                }
            }
        }


        b = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (A[i][j] == 'B') {
                    I[i][j] = 1<<(t + (b++));
                } else if (A[i][j] >= '1' && A[i][j] <= '8') {
                    I[i][j] = 1<<(A[i][j] - '1');
                }
            }
        }

        int L = b + t;
        vector<int> X(t); cin >> X;
        vector2<int> Left(N, M, 0);
        for (int i = 0; i < N; ++i) {
            int left = 0;
            for (int j = 0; j < M; ++j) {
                Left[i][j] = left;
                left |= I[i][j];
            }
        }

        ui id = (S.x + S.y * N) << L;
        vector<int> D(1+(N*M<<L), 10000);
        D[id] = 0;
        int E[4];
        vector<ui> Q{id};
        for (int i = 0; i < Q.size(); ++i) {
            ui id = Q[i];

            ui a = (id>>L) % N;
            ui b = (id>>L) / N;

            if (a != 0 && A[a-1][b] == '.') E[0] = (id^Left[a][b]) - (1<<L); else E[0] = -1;
            if (a != N-1 && A[a+1][b] == '.') E[1] = (id^Left[a+1][b]) + (1<<L); else E[1] = -1;
            if (b != 0 && A[a][b-1] == '.') E[2] = id - (N<<L); else E[2] = -1;
            if (b != M-1 && A[a][b+1] == '.') E[3] = id + (N<<L); else E[3] = -1;

                for (int u : E) {
                if (u != -1 && D[u] == 10000) {
                    D[u] = D[id] + 1;
                    Q.push_back(u);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < (1<<t); ++i) {
            int cur = 0;
            for (int j = 0; j < t; ++j) if (i&1<<j) cur += X[j];
            ans = max(ans, cur - D[id++]);
        }
        cout << ans << '\n';
    }
};
