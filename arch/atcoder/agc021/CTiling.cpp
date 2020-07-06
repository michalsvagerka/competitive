#include "../l/lib.h"

class CTiling {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        int A, B; cin >> A >> B;
        if (2*(A+B) > N*M) {
            cout << "NO\n";
            return;
        }

        vector<string> C(N, string(M, '.'));
        if (N%2 == 1) {
            for (int i = 0; i+1 < M; i += 2) {
                if (A) {
                    C[N-1][i] = '<';
                    C[N-1][i+1] = '>';
                    --A;
                }
            }
        }

        if (M % 2 == 1) {
            for (int i = 0; i + 4 <= N; i += 2) {
                if (B) {
                    C[i][M-1] = '^';
                    C[i+1][M-1] = 'v';
                    --B;
                }
            }
            if (B > 0 && N >= 2) {
                C[N-2][M-1] = '^';
                C[N-1][M-1] = 'v';
                --B;
            }
        }

        for (int i = 0; i + 1 < N; i += 2) {
            for (int j = 0; j + 1 < M; j += 2) {
                if (A >= 2) {
                    C[i][j] = '<';
                    C[i][j+1] = '>';
                    C[i+1][j] = '<';
                    C[i+1][j+1] = '>';
                    A -= 2;
                } else if (B >= 2) {
                    C[i][j] = '^';
                    C[i][j+1] = '^';
                    C[i+1][j] = 'v';
                    C[i+1][j+1] = 'v';
                    B -= 2;
                } else if (B >= 1) {
                    C[i][j] = '^';
                    C[i+1][j] = 'v';
                    --B;
                } else if (A >= 1) {
                    C[i][j] = '<';
                    C[i][j+1] = '>';
                    --A;
                }
            }
        }

        if (N % 2 == 1 && M % 2 == 1) {
            if (A == 1 && N >= 3 && M >= 2 && C[N-3][M-2] == '.') {
                C[N-3][M-2] = '<';
                C[N-3][M-1] = '>';
                --A;
            }
        }

        if (A == 0 && B == 0) {
            cout << "YES\n";
            for (string &c: C) cout << c << '\n';
        } else {
            cout << "NO\n";
        }
    }
};
