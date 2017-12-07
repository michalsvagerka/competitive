#include "../l/lib.h"
#include "../l/util.h"

class randommaze {
public:
    void solve(istream& cin, ostream& cout) {
        int R,C,seed; cin >> R >> C >> seed;
        vector<pair<int,pii>> Z;
        for (int r = 1; r < 2*R; ++r) {
            for (int c = 0; c + r%2 < C; ++c) {
                seed = (seed * 25173 + 13849) & 65535;
                Z.push_back({seed, {r,c}});
            }
        }

        sort(Z.begin(),Z.end());
        reverse(Z.begin(),Z.end());

        UnionFind U((R+1)*(C+1));
        for (int c = 0; c < C; ++c) {
            U.unite(c, c+1);
            U.unite(R*(C+1)+c, R*(C+1)+c+1);
        }
        for (int r = 0; r < R; ++r) {
            U.unite(r*(C+1), (r+1)*(C+1));
            U.unite(r*(C+1)+C, (r+1)*(C+1)+C);
        }

        vector2<bool> Q(2*R, C, false);

        for (auto z: Z) {
            int r = z.y.x, c = z.y.y, a = (r/2)*(C+1) + c, b = a + 1;
            if (r%2) {
                a ++;
                b += C + 1;
            }

            Q[r][c] = U.unite(a,b);
        }

        for (int c = 0; c < C; ++c) cout << "+-";
        cout << "+\n";
        for (int r = 1; r < 2*R; ++r) {
            if (r%2) {
                cout << "| ";
                for (int c = 0; c < C - 1; ++c) cout << " |"[Q[r][c]] << " ";
                cout << "|\n";
            } else {
                for (int c = 0; c < C; ++c) cout << "+" << " -"[Q[r][c]];
                cout << "+\n";
            }
        }

        for (int c = 0; c < C; ++c) cout << "+-";
        cout << "+\n";
    }
};
