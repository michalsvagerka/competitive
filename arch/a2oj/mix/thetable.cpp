#include "../../../l/lib.h"
// #include "../l/mod.h"

class thetable {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N,M); cin >> A;
        vector<bool> S(N), T(M);

        while (true) {
            for (int i = 0; i < N; ++i) {
                int s = 0;
                for (int j = 0; j < M; ++j) s += A[i][j];
                if (s < 0) {
                    S[i] = !S[i];
                    for (int j = 0; j < M; ++j) A[i][j] = -A[i][j];
                }
            }


            bool u = false;
            for (int i = 0; i < M; ++i) {
                int s = 0;
                for (int j = 0; j < N; ++j) s += A[j][i];
                if (s < 0) {
                    T[i] = !T[i];
                    u = true;
                    for (int j = 0; j < N; ++j) A[j][i] = -A[j][i];
                }
            }

            if (!u) break;
        }

        vector<int> W,Z;
        for (int i = 0; i < N; ++i) if (S[i]) W.push_back(i+1);
        for (int i = 0; i < M; ++i) if (T[i]) Z.push_back(i+1);
        cout << W.size() << ' ' << W;
        cout << Z.size() << ' ' << Z;

    }
};
