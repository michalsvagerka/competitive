#include "../l/lib.h"

class ohrozfigury {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> A(N); cin >> A;
        int kr, kc;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 'K') {
                    kr = i;
                    kc = j;
                }
            }
        }

        int ans = 0;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (A[r][c] == '*') {
                    if (abs(kr-r) <= 1 && abs(kc-c) <= 1) continue;
                    if (r == N-1) {
                        cout << -1 << endl;
                        return;
                    }
                    if (c != 0 && A[r+1][c-1] == 'P') continue;
                    if (c != N-1 && A[r+1][c+1] == 'P') continue;
                    if (c != N-1 && A[r+1][c+1] == '-') {
                        A[r+1][c+1] = 'P';
                        ans++;
                        continue;
                    }
                    if (c != 0 && A[r+1][c-1] == '-') {
                        A[r+1][c-1] = 'P';
                        ans++;
                        continue;
                    }
                    cout << -1 << endl;
                    return;
                }
            }
        }
        cout << ans << '\n';
    }
};
