#include "../l/lib.h"
 #include "../l/graph.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
//    int R = 1;
//    for (int S = 6; S < 20; ++S) {
//        Bipartite B(R*S, R*S);
//        for (int r = 0; r < R; ++r) {
//            for (int c = 0; c < S; ++c) {
//                for (int a = 0; a < R; ++a) {
//                    for (int b = 0; b < S; ++b) {
//                        if (abs(a - r) + abs(c - b) == 3) {
//                            if ((r + c) % 2 == 0) {
//                                B.addEdge(r*S + c, R*S + a*S + b);
//                            } else {
//                                B.addEdge(a*S + b, R*S + r*S + c);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        if (2*B.matchingSize() != R*S)
//        cout << S << ' ' << 2*B.matchingSize() << endl;
//    }

    int N, M; cin >> N >> M;
    if (N > M) swap(N, M);
    if (N == 1) {
        cout << 6 * (M/6) + 2 * max(0, M%6-3) << endl;
    } else if (N == 2) {
        if (M == 2) cout << 0 << endl;
        else if (M == 3) cout << 4 << endl;
        else if (M == 7) cout << 12 << endl;
        else cout << 2*M << endl;
    } else {
        ll z = ll(N)*M;
        cout << z - (z%2) << endl;
    }
}
};
