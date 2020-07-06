#include "../l/lib.h"

class boca {
public:
    int N, R, C;
    ll D;
    vector<pair<pii, int>> W;
    bool possible;
    ll ans;
    vector2<ll> MIN, MAX;

    void calc() {
        MIN = vector2<ll>(R,C,-1000000000000000000LL);
        MAX = vector2<ll>(R,C,1000000000000000000LL);
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                for (int i = 0; i < N; ++i) {
                    int dist = abs(r-W[i].x.x) + abs(c-W[i].x.y);
                    MIN[r][c] = max(MIN[r][c], W[i].y - D*dist);
                    MAX[r][c] = min(MAX[r][c], W[i].y + D*dist);
                }
                if (MIN[r][c] > MAX[r][c]) {
                    possible = false;
                    return;
                } else {
                    ans += MIN[r][c];// % 1000000007;
                }
            }
        }

    }

    void read(istream& cin) {
        cin >> R >> C >> N;
        D = 1;
        for (int i = 0; i < N; ++i) {
            int x,y,V; cin >> x >> y >> V;
            W.push_back({{x-1,y-1},  V});
        }
        possible = true;
        ans = 0;
    }

    void write(ostream &cout) {
        if (possible) {
            cout << ans;
        } else {
            cout << "No";
        }
        cout << endl;
    }

    void solve(istream& cin, ostream& cout) {
        read(cin);
        calc();
        write(cout);
    }
};
