#include "../../../l/lib.h"
// #include "../l/mod.h"

class boardgame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int M = 1<<logceil(N);

        vector<pair<pair<pii, pii>, int>> S(N);
        for (int i = 0; i < N; ++i) {
            cin >> S[i].x;
            S[i].y = i+1;
        }
        if (S[N-1].x.x == pii{0,0}) {
            cout << "1\n" << N << "\n";
            return;
        }

        sort(S.begin(),S.end());

        vector<int> LO(2*M, 2e9), P(N, -1), Q;
        for (int i = 0; i < N; ++i) {
            if (S[i].x.x == pii{0,0}) {
                Q.push_back(i);
            } else {
                LO[M+i] = S[i].x.x.y;
            }
        }
        for (int i = M - 1; i >= 1; --i) LO[i] = min(LO[2*i], LO[2*i+1]);

        for (int q = 0; q < Q.size(); ++q) {
            int p = Q[q];
            int x = S[p].x.y.x;
            int y = S[p].x.y.y;
            while (true) {
                int i = 1;
                while (i < M) i = 2*i+(LO[2*i] > y);
                i -= M;
                if (i < N && S[i].x.x.y <= y && S[i].x.x.x <= x) {
                    P[i] = p;
                    Q.push_back(i);
                    i += M;
                    LO[i] = 2e9;
                    while (i > 1) {
                        i /= 2;
                        LO[i] = min(LO[2*i], LO[2*i+1]);
                    }
                } else {
                    break;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (S[i].y == N) {
                if (P[i] != -1) {
                    vector<int> Solution{N};
                    int x = i;
                    while (P[x] != -1) {
                        x = P[x];
                        Solution.push_back(S[x].y);
                    }

                    reverse(Solution.begin(), Solution.end());
                    cout << Solution.size() << endl << Solution;
                } else {
                    cout << "-1\n";
                }
            }
        }
    }
};
