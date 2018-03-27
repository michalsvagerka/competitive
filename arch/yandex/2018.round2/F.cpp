#include "../../../l/lib.h"
// #include "../l/mod.h"

class F {
public:
    struct Path {
        int thisX;
        int topY, bottomY;
        int bottomMostY;

        explicit Path(pii p) {
            int x = p.x;
            int y = -p.y;

            thisX = x;
            topY = bottomY = y;
            bottomMostY = 0;
        }

        bool canPut(pii p) const {
            int x = p.x;
            int y = -p.y;
            if (x == thisX && y == bottomY - 1 && y >= bottomMostY) {
                return true;
                //--bottomY;
            } else if (x == thisX+1 && y >= topY) {
                return true;
            } else return y > topY;
        }

        void put(pii p) {
            int x = p.x;
            int y = -p.y;
            if (x == thisX && y == bottomY - 1 && y >= bottomMostY) {
                --bottomY;
            } else {
                if (x == thisX+1 && y >= topY) {
                    bottomMostY = bottomY;
                } else {
                    bottomMostY = topY + 1;
                }

                thisX = x;
                topY = bottomY = y;
            }
        }

    };

    void solve(istream& cin, ostream& cout) {
        int N, M, K; cin >> N >> M >> K;
        set<pii> S;
        for (int i = 0; i < K; ++i) {
            int a,b; cin >> a >> b;
            S.insert({a,-b});
        }

        vector<Path> P;
        for (pii s: S) {
            int z = P.empty() ? -1 : bsl(0, (int)P.size()-1, [&](int i) { return P[i].canPut(s); });
            if (z != -1) {
                P[z].put(s);
            } else {
                P.push_back(Path{s});
            }
        }


        bool hasBottomRight = S.find({N-1,0}) != S.end();
        cout << 2 * P.size() - hasBottomRight << endl;
    }
};
