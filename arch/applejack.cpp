#include "../l/lib.h"
// #include "../l/mod.h"

class applejack {
public:
    void solve(istream& cin, ostream& cout) {
        set<int> C;
        int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1,x2);
        if (y1 > y2) swap(y1,y2);
        C.insert(x1);
        C.insert(x2);
        C.insert(y1);
        C.insert(y2);
        int N; cin >> N;
        vector<pair<pii,pii>> V(N);
        for (int i = 0; i < N; ++i) {
            cin >> V[i].x.x >> V[i].x.y >> V[i].y.x >> V[i].y.y;
            if (V[i].x.x > V[i].y.x) swap(V[i].x.x,V[i].y.x);
            if (V[i].x.y > V[i].y.y) swap(V[i].x.y,V[i].y.y);
            C.insert(V[i].x.x);
            C.insert(V[i].x.y);
            C.insert(V[i].y.x);
            C.insert(V[i].y.y);
        }

        map<int,int> M; int s = 0;
        for (int c:C) M[c] = s++;

        vector2<bool> Z(s-1,s-1,false);
        for (int x = M[x1]; x < M[x2]; ++x) {
            for (int y = M[y1]; y < M[y2]; ++y) {
                Z[x][y] = true;
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int x = M[V[i].x.x]; x < M[V[i].y.x]; ++x) {
                for (int y = M[V[i].x.y]; y < M[V[i].y.y]; ++y) {
                    Z[x][y] = false;
                }
            }
        }

        int ans = 0;
        for (int x = 0; x < s-1; ++x) {
            for (int y = 0; y < s-1; ++y) {
                if (Z[x][y]) {
                    ans++;
                    vector<pii> Q{{x,y}};
                    for (int i = 0; i < Q.size(); ++i) {
                        int r = Q[i].x, c = Q[i].y;
                        if (!in(0,r,s-1) || !in(0,c,s-1) || !Z[r][c]) continue;
                        Z[r][c] = false;
                        Q.push_back({r+1,c});
                        Q.push_back({r-1,c});
                        Q.push_back({r,c+1});
                        Q.push_back({r,c-1});
                    }
                }
            }
        }
        cout << ans << endl;
    }
};
