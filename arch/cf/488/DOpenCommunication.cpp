#include "../../../l/lib.h"

class DOpenCommunication {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> A(N), B(M); cin >> A >> B;
        vector2<int> Common(N, M, -1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (set<int>{A[i].x,A[i].y,B[j].x,B[j].y}.size() == 3) {
                    if (A[i].x == B[j].x || A[i].x == B[j].y) Common[i][j] = A[i].x;
                    else Common[i][j] = A[i].y;
                }
            }
        }

        vector<bool> F(10, false);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (Common[i][j] != -1) F[Common[i][j]] = true;
            }
        }

        if (count(F.begin(),F.end(),true) == 1) {
            for (int i = 0; i < 10; ++i) {
                if (F[i]) {
                    cout << i << '\n';
                    return;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            vector<bool> G(10, false);
            for (int j = 0; j < M; ++j) {
                if (Common[i][j] != -1) G[Common[i][j]] = true;
            }
            if (count(G.begin(),G.end(),true) >= 2) {
                cout << -1 << endl;
                return;
            }
        }

        for (int j = 0; j < M; ++j) {
            vector<bool> G(10, false);
            for (int i = 0; i < N; ++i) {
                if (Common[i][j] != -1) G[Common[i][j]] = true;
            }
            if (count(G.begin(),G.end(),true) >= 2) {
                cout << -1 << endl;
                return;
            }
        }

        cout << 0 << endl;
    }
};
