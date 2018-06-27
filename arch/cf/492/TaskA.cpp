#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N, K;
    cin >> N >> K;
    vector2<int> X(4, N);
    cin >> X;
    vector<pair<int, pii>> A;
    bool empty = false;
    vector<pii> Z;
    for (int i = 0; i < N; ++i) {
        Z.push_back({1,i});
    }
    for (int i = 0; i < N; ++i) {
        Z.push_back({2,N-1-i});
    }

    for (int r = 0; r < 2 * N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (X[0][c] == X[1][c] && X[0][c] != 0) {
                A.push_back({X[1][c], {1, c+1}});
                X[1][c] = 0;
            }
            if (X[3][c] == X[2][c] && X[2][c] != 0) {
                A.push_back({X[2][c], {4, c+1}});
                X[2][c] = 0;
            }
            empty |= X[1][c] == 0;
            empty |= X[2][c] == 0;
        }
        if (!empty) {
            cout << "-1\n";
            return;
        }

        while (X[Z[0].x][Z[0].y]) rotate(Z.begin(),Z.begin()+1,Z.end());
        for (int z = 0; z < 2*N-1; ++z) {
            if (X[Z[z+1].x][Z[z+1].y]) {
                A.push_back({X[Z[z+1].x][Z[z+1].y], {Z[z].x+1, Z[z].y+1}});
                X[Z[z].x][Z[z].y] = X[Z[z+1].x][Z[z+1].y];
                X[Z[z+1].x][Z[z+1].y] = 0;
            }
        }
    }

    cout << A.size() << '\n';
    for (auto &a: A) cout << a << '\n';
}
};
