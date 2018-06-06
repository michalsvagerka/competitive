#include "../l/lib.h"
// #include "../l/mod.h"

class grippingstory {
public:
    int dist(int x, int y, int X, int Y) {
        int dx = abs(x-X);
        int dy = abs(y-Y);
        if (dx > 1e9 || dy > 1e9) return 1e9+1;
        ll d2 = ll(dx)*dx + ll(dy)*dy;
        ll d = sqrt(double(d2));
        while (d*d > d2) --d;
        while (d*d < d2) ++d;
        return int(d);
    }

    void solve(istream& cin, ostream& cout) {

        int X, Y; cin >> X >> Y;
        int W, R; cin >> W >> R;

        int N; cin >> N;
        int M = 1<<logceil(N+1);

        vector<pair<pii, pii>> S(N+1);
        S[0] = {{0,0},{R,W}};
        for (int i = 0; i < N; ++i) {
            int x,y,m,p,r;
            cin >> x >> y >> m >> p >> r;
            S[i+1] = {{dist(x,y,X,Y), m}, {r,p}};
        }

        sort(S.begin(),S.end());
        vector<int> LO(2*M, 2e9), P(N+1, -1), Q;
        for (int i = 0; i < N+1; ++i) {
            if (S[i].x == pii{0,0}) {
//                cout << "starting " << i << endl;
                Q.push_back(i);
            } else {
                LO[M+i] = S[i].x.y;
            }
        }
        for (int i = M - 1; i >= 1; --i) LO[i] = min(LO[2*i], LO[2*i+1]);

        for (int q = 0; q < Q.size(); ++q) {
//            cout << "process " << Q[q] << endl;
            int p = Q[q];
            int x = S[p].y.x;
            int y = S[p].y.y;
            while (true) {
                int i = 1;
                while (i < M) i = 2*i+(LO[2*i] > y);
                i -= M;
                if (i < N+1 && S[i].x.y <= y && S[i].x.x <= x) {
//                    cout << "get " << i << endl;
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
        int ans = 0;
        for (int i = 0; i < N+1; ++i) ans += P[i] != -1;
        cout << ans << endl;

    }
};
