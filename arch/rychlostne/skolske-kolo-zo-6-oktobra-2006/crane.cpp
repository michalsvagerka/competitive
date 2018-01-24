#include "../l/lib.h"
#include "../l/geo.h"

class crane {
public:
    void solve(istream& cin, ostream& cout) {
        ui X,Y,N;
        cin >> X >> Y >> N;
        vector<Circle<ui>> C(N);
        for (int i = 0; i < N; ++i) {
            cin >> C[i].center.x >> C[i].center.y >> C[i].radius;
        }

        Point<ui> O{X/2,0};
        vector<bool> V(N,false);
        vector<ui> Q;
        for (int i = 0; i < N; ++i) {
            if (C[i].contains(O)) {
                Q.push_back(i);
                V[i] = true;
            }
        }

        for (int i = 0; i < Q.size(); ++i) {
            for (int j = 0; j < N; ++j) {
                if (!V[j] && C[Q[i]].intersect(C[j])) {
                    V[j] = true;
                    Q.push_back(j);
                }
            }
        }

        ui K; cin >> K;
        for (int i = 0; i < K; ++i) {
            Point<ui> p; cin >> p.x >> p.y;
            bool found = false;
            for (ui q:Q) {
                found |= C[q].contains(p);
            }
            cout << (found ? "YES" : "NO") << '\n';
        }
    }
};
