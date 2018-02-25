#include "../../../l/lib.h"
#include "../../../l/flow.h"

class tiles {
public:
    void solve(istream& cin, ostream& cout) {
        int R, C; cin >> R >> C;
        vector<string> S(R); cin >> S;

        PushRelabel<int> G(2*R*C+2);
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (S[r][c] == 'X') continue;
                int me = 1 + r * C + c;
                if (r % 2 == 0) {
                    if ((r + c) % 2 == 1) {
                        G.AddEdge(0, me);
                    } else {
                        G.AddEdge(me, me+R*C);
                        if (r != 0) G.AddEdge(me + R*C, me - C + R*C);
                        if (r != R-1) G.AddEdge(me + R*C, me + C + R*C);
                        if (c != 0) G.AddEdge(me - 1, me);
                        if (c != C-1) G.AddEdge(me + 1, me);
                    }
                } else {
                    if ((r + c) % 2 == 1) {
                        G.AddEdge(me + R * C, 2 * R * C + 1);
                    } else {
                        G.AddEdge(me, me+R*C);
                        if (r != 0) G.AddEdge(me - C, me);
                        if (r != R-1) G.AddEdge(me + C, me);
                        if (c != 0) G.AddEdge(me + R*C, R * C + me - 1);
                        if (c != C-1) G.AddEdge(me + R*C, R * C + me + 1);
                    }
                }
            }
        }

        cout << G.GetMaxFlow(0, 2*R*C+1) << endl;
    }
};
