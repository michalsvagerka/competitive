#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector2<string> S(N, M); cin >> S;
    vector2<string> T(N, M); cin >> T;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            reverse(S[i][j].begin(),S[i][j].end());
            reverse(T[i][j].begin(),T[i][j].end());
        }
    }

    vector<vector<pair<pii,pii>>> C(8);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == 0 && j == 0) continue;
            if (i == 1 && j == 1) continue;
            for (char c:S[i][j]) {
                int q = c-'0';
                if (i == q) {
                    C[0].push_back({{i,j},{q,q}});
                } else if (j == q) {
                    C[0].push_back({{i,j},{q,q}});
                } else {
                    C[0].push_back({{i,j},{i,q}});
                    C[1].push_back({{i,q},{q,q}});
                }
            }
        }
    }

    for (char c: S[0][0]) {
        int q = c-'0';
        C[2].push_back({{0,0},{1,0}});
        C[2].push_back({{1,0},{q,q}});
    }


    for (char c: S[1][1]) {
        int q = c-'0';
        C[2].push_back({{1,1},{1,0}});
        C[2].push_back({{1,0},{q,q}});
    }


    for (int i = 0; i < N; ++i) {
        for (int j = 2; j < M; ++j) {
            for (char c: T[i][j]) {
                int q = c-'0';
                if (i == q) {
                    C[3].push_back({{q,q},{i,j}});
                } else if (j == q) {
                    C[3].push_back({{q,q},{i,j}});
                } else {
                    C[3].push_back({{q,q},{i,q}});
                    C[3].push_back({{i,q},{i,j}});
                }
            }
        }
    }

    for (int i = 2; i < N; ++i) {
        for (int j = 0; j <= 1; ++j) {
            for (char c: T[i][j]) {
                int q = c-'0';
                if (i == q) {
                    C[4].push_back({{q,q},{i,j}});
                } else if (j == q) {
                    C[4].push_back({{q,q},{i,j}});
                } else {
                    C[4].push_back({{q,q},{q,j}});
                    C[4].push_back({{q,j},{i,j}});
                }
            }
        }
    }

    for (char c: T[0][0]) {
        int q = c-'0';
        C[5].push_back({{q,q},{1,0}});
        C[7].push_back({{1,0},{0,0}});
    }


    for (char c: T[1][1]) {
        int q = c-'0';
        C[5].push_back({{q,q},{0,1}});
        C[7].push_back({{0,1},{1,1}});
    }

    for (char c: T[1][0]) {
        int q = c-'0';
        C[6].push_back({{q,q},{1,0}});
    }

    for (char c: T[0][1]) {
        int q = c-'0';
        C[6].push_back({{q,q},{0,1}});
    }


    int ans = 0;
    for (int i = 0; i < C.size(); ++i) {
        ans += C[i].size();
    }

    cout << ans << endl;
    for (int i = 0; i < C.size(); ++i) {
        for (auto &c:C[i]) {
            cout << c.x.x+1 << ' ' << c.x.y+1 << ' ' << c.y.x+1 << ' ' << c.y.y+1 << '\n';
        }
    }

}

};
