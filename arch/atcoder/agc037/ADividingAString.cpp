#include "../l/lib.h"

class ADividingAString {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        int G = 4;
        vector2<int> MX(N+1, G, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= G; ++j) {
                for (int k = 1; k <= G; ++k) {
                    if (i + k > N) continue;

                    bool ok = true;
                    if (j == k && j <= i) {
                        ok = false;
                        for (int l = 0; l < j; ++l) {
                            if (S[i+l] != S[i+l-k]) ok = true;
                        }
                    }

                    if (ok) {
                        MX[i+k][k-1] = max(MX[i+k][k-1], MX[i][j-1] + 1);
                    }
                }
            }
        }

        cout << *max_element(MX[N].begin(),MX[N].end()) << endl;
    }
};
