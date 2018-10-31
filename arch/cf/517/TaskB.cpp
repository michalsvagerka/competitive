#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, K;
    cin >> N >> K;
    vector<string> S(N);
    cin >> S;

    vector2<int> O(N, N, -1);
    O[N - 1][N - 1] = 0;
    for (int d = 2 * N - 3; d >= 1; --d) {
        vector<pair<pii, pii>> Z;
        for (int r = 0; r < N; ++r) {
            int c = d - r;
            if (c >= 0 && c < N) {
                int q = N;
                if (r < N - 1) q = min(q, O[r + 1][c]);
                if (c < N - 1) q = min(q, O[r][c + 1]);
                Z.push_back({{S[r][c]-'a', q}, {r, c}});
            }
        }
        sort(Z.begin(), Z.end());
        for (int i = 0; i < Z.size(); ++i) {
            auto &z = Z[i];
            O[z.y.x][z.y.y] = i;
        }
    }

    vector2<int> D(N, N, 10000);
    D[0][0] = 0;
    for (int d = 0; d <= 2 * N - 3; ++d) {
        for (int r = 0; r < N; ++r) {
            int c = d - r;
            if (c >= 0 && c < N) {
                int k = D[r][c] + (S[r][c] != 'a');
                if (r < N - 1) D[r + 1][c] = min(D[r + 1][c], k);
                if (c < N - 1) D[r][c + 1] = min(D[r][c + 1], k);
            }
        }
    }

    for (int d = 2 * N - 2; d >= 0; --d) {
        pii ans = {10000, -1};
        for (int r = 0; r < N; ++r) {
            int c = d - r;
            if (c >= 0 && c < N) {
                if (D[r][c] <= K) {
                    ans = min(ans, {O[r][c], r});
                }
            }
        }
        if (ans.x != 10000) {
            for (int i = 0; i < d; ++i) cout << 'a';
            int r = ans.y;
            int c = d - r;
            if (D[r][c] < K) cout << 'a'; else cout << S[r][c];

            while (r + c < 2 * N - 2) {
                if (r == N - 1) {
                    c++;
                } else if (c == N - 1) {
                    r++;
                } else {
                    if (O[r + 1][c] < O[r][c + 1]) ++r; else ++c;
                }

                cout << S[r][c];
            }
            cout << endl;
            return;
        }
    }
}   
};
