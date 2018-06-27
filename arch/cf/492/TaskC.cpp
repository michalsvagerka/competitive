#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    vector<int> C;
    vector<pair<pii,int>> V;
    int N;

    ll dist(const pii&x) {
        return ll(x.x)*ll(x.x) + ll(x.y)*ll(x.y);
    };

    bool brute(int j, pii X) {
        if (j == N) {
            return dist(X) <= 2250000000000LL;
        }
        if (j > 5) {
            for (int i = j; i < N; ++i) {
                pii Y{X.x + V[i].x.x, X.y + V[i].x.y};
                pii Z{X.x - V[i].x.x, X.y - V[i].x.y};
                if (dist(Y) <= dist(Z)) {
                    X = Y;
                    C[V[i].y] = 1;
                } else {
                    X = Z;
                    C[V[i].y] = -1;
                }
            }

            return dist(X) <= 2250000000000LL;
        } else {
            pii Y{X.x + V[j].x.x, X.y + V[j].x.y};
            pii Z{X.x - V[j].x.x, X.y - V[j].x.y};
            C[V[j].y] = 1;
            if (brute(j+1, Y)) return true;
            C[V[j].y] = -1;
            if (brute(j+1, Z)) return true;
            return false;
        }
    }

void solve(istream& cin, ostream& cout) {
    cin >> N;
    C.resize(N);
    V.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> V[i].x;
        V[i].y = i;
    }
    sort(V.begin(),V.end(), [&](const pair<pii,int>&x, const pair<pii,int>&y) { return dist(x.x) > dist(y.x); });
    brute(0, {0,0});
    cout << C;
}
};
