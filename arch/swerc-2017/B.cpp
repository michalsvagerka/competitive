#include "../../l/lib.h"
#include "../../l/segtree.h"

class B {
public:
    vector<vector<int>> S;

    void split(SetMinTree<pii> &T, int p, int f, int t) {
        if (f > t) return;

        auto x = T.get(f,t);
        int h = t-f+1;
        int w = x.x;
        // for (int ww = p+1; ww <= w; ++ww)  cerr << h << '*' << ww << endl;

        S[h][w]++;
        S[h][p]--;

        split(T,x.x,f,x.y-1);
        split(T,x.x,x.y+1,t);
    }

    void solve(istream& cin, ostream& cout) {
        int X,Y,N,D;
        cin >> X >> Y >> N >> D;
        vector<set<int>> F(X);
        for (int i = 0; i < N; ++i) {
            int x1,y1,x2,y2;
            cin >> x1 >> x2 >> y1 >> y2;
            for (int j = x1; j < x2; ++j) {
                for (int k = y1; k < y2; ++k) {
                    F[j].insert(k);
                }
            }
        }

        for (int i = 0; i < X; ++i) {
            F[i].insert(Y);
        }

        S = vector2<int>(X+1,Y+1,0);
        for (int y = 0; y < Y; ++y) {
            vector<pii> M(X);
            for (int i = 0; i < X; ++i) {
                M[i] = {*F[i].lower_bound(y) - y,i};
            }
            SetMinTree<pii> T;
            T.setup(M,{10000,10000});
            split(T, 0, 0, X-1);
            // cerr << "next" << endl;
            //cerr << T.get(0, X-1).x << endl;
        }

        for (int l = 0; l <= X; ++l) {
            for (int i = Y; i > 0; --i) {
                S[l][i-1] += S[l][i];
            }
        }

        // cerr << S;

        for (int y = 0; y <= Y; ++y) {
            int c = 0, s = 0;
            for (int x = X; x > 0; --x) {
                int q = S[x][y];
                S[x][y] += c+s;
                s += q;
                c += s;
            }
        }

        // cerr << S;

        for (int d = 0; d < D; ++d) {
            int a,b; cin >> a >> b;
            cout << S[a][b] << '\n';
        }


    }
};
