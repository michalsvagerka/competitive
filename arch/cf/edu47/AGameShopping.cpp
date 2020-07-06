#include "../l/lib.h"

class AGameShopping {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N), B(M); cin >> A >> B;
        int j = 0;
        for (int i = 0; i < N; ++i) {
            if (j < M && A[i] <= B[j]) ++j;
        }
        cout << j << '\n';
    }
};
