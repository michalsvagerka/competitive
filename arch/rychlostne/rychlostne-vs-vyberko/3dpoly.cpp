#include "../l/lib.h"
// #include "../l/mod.h"

int steps[] = {2,3,2,1,0,0};

class poly {
public:
    typedef pair<int, pii> point;

    point rotate(point &p, int r) {
        if (r==0) {
            return {-p.y.x, {p.x, p.y.y}};
        } else if (r==1) {
            return {-p.y.y, {p.y.x,p.x}};
        } else if (r==2){
            return {p.x, {-p.y.y, p.y.x}};
        } else if (r==3) {
            return {-p.x, p.y};
        } else if (r==4) {
            return {p.x, {-p.y.x, p.y.y}};
        } else {
            return {p.x, {p.y.x, -p.y.y}};
        }
    }

    void normalize(vector<point>&E) {
        int mx = 100000, my = 100000, mz = 100000;

        for (point&e:E) {
            mx = min(mx, e.x);
            my = min(my, e.y.x);
            mz = min(mz, e.y.y);
        }
        for (point&e: E) {
            e.x -= mx;
            e.y.x -= my;
            e.y.y -= mz;
        }
        sort(E.begin(), E.end());
    }

    vector<point> rotate(const vector<point> &E, int r) {
        vector<point> R;
        for (point e: E) R.push_back({rotate(e, r)});
        return R;
    }

    bool contained(vector<point> &a, const set<vector<point>> &R, int i) {
        if (i==6) {
            normalize(a);
            return R.find(a) != R.end();
        }

        if (contained(a,R,i+1)) return true;
        for (int j = 0; j < steps[i]; ++j) {
            a=rotate(a,i);
            if (contained(a,R,i+1)) return true;
        }
        return false;
    }

    void insert(const vector<point> &P, const point& np, set<vector<point>> &R) {
        if (find(P.begin(),P.end(), np) == P.end()) {
            vector<point> NP(P);
            NP.push_back(np);
            if (!contained(NP,R,0)) {
                normalize(NP);
                R.insert(NP);
//                cerr << "New poly: " << NP.size() << ": ";
//                for (point&p:NP) cerr << " (" << p.x << ',' << p.y.x << ',' << p.y.y << ") ";
//                cerr << endl;
            }
        }
    }

    void generateNeighbors(const vector<point> &P, set<vector<point>> &R) {
        for (point e:P) {
            e.x++;
            insert(P, e, R);
            e.x -= 2;
            insert(P, e, R);
            e.x++;

            e.y.x++;
            insert(P, e, R);
            e.y.x -= 2;
            insert(P, e, R);
            e.y.x++;

            e.y.y++;
            insert(P, e, R);
            e.y.y -= 2;
            insert(P, e, R);
            e.y.y++;
        }
    }

    vector<int> size(const vector<point> &p) {
        int mx = 0, my = 0, mz = 0;
        for (auto &e:p) {
            mx = max(mx, e.x);
            my = max(my, e.y.x);
            mz = max(mz, e.y.y);
        }
        vector<int> R{mx+1,my+1,mz+1};
        sort(R.begin(),R.end());
        return R;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> D(3); cin >> D;
        sort(D.begin(),D.end());

        vector<set<vector<point>>> R(N);
        R[0].insert({{0,{0,0}}});
        for (int i = 1; i < N; ++i) {
            for (auto &points:R[i-1]) {
                generateNeighbors(points, R[i]);
            }
        }

        int ans = 0;
        for (auto&poly: R[N-1]) {
            auto s = size(poly);
            ans += s[0] <= D[0] && s[1] <= D[1] && s[2] <= D[2];
        }
        cout << ans << endl;
    }
};
