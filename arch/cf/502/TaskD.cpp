#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, Q; cin >> N >> M >> Q;
    vector<int> W(N); cin >> W;
    vector<int> C(1<<N, 0);
    for (int i = 0; i < M; ++i) {
        string S; cin >> S;
        int z = 0;
        for (int j = 0; j < N; ++j) {
            if (S[j] == '1') z |= 1<<j;
        }
        C[z]++;
    }

    vector2<int> D(1<<N, 105, 0);
    for (int i = 0; i < (1<<N); ++i) {
        for (int j = 0; j < (1<<N); ++j) {
            int ans = 0;
            for (int k = 0; k < N; ++k) {
                if ((i&(1<<k)) == (j&(1<<k))) ans += W[k];
            }
            if (ans <= 104) D[i][ans] += C[j];
        }


        for (int j = 0; j < 103; ++j) D[i][j+1] += D[i][j];
    }

    for (int i = 0; i < Q; ++i) {
        string T; int K; cin >> T >> K;
        int z = 0;
        for (int j = 0; j < N; ++j) {
            if (T[j] == '1') z |= 1<<j;
        }
        cout << D[z][K] << '\n';
    }

}
};
