#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/frac.h"

typedef Field<998244353> FF;
constexpr ll INF = 1e12;

class DLCC {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> X(N), V(N), P(N);
        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> V[i] >> P[i];
        }

        vector<tuple<Fraction, int, int>> Events;
        for (int i = 0; i < N - 1; ++i) {
            Events.push_back({{X[i+1]-X[i],V[i] + V[i+1]}, i, 1});
            if (V[i+1] != V[i]) {
                Events.push_back({{X[i+1]-X[i], abs(V[i+1]-V[i])}, i, 2 + (V[i+1]<V[i])});
            }
        }
        // 1 -- towards each other
        // 2 -- both to the left
        // 3 -- both to the right

        sort(Events.begin(),Events.end());
        vector<bool> MustBeLeft(N, false), MustBeRight(N, false);
        vector<bool> Meet(N, false);
        struct Node {
            FF x[4];
            int l, r;
            Node() {}
        };

        auto empty = [&](int i) {
            Node n;
            n.r = false;
            n.x[0] = n.x[1] = n.x[2] = 0;
            n.x[3] = 1;
            return n;
        };

        auto build = [&](int i) {
            Node n;
            n.r = Meet[i];
            n.x[0] = MustBeRight[i] ? 0 : 100-P[i];
            n.x[3] = MustBeLeft[i] ? 0 : P[i];
            n.x[1] = n.x[2] = 0;
            return n;
        };

        auto combine = [&](Node &a, Node &b) {
            Node n;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (a.r && (i&2) && (j&1)==0) continue;
                    n.x[(i&1)|(j&2)] += a.x[i] * b.x[j];
                }
            }
            n.r = b.r;
            return n;
        };

        int M = 1<<logceil(N);
        vector<Node> TT(2*M);
        for (int i = 0; i < N; ++i) TT[M+i] = build(i);
        for (int i = N; i < M; ++i) TT[M+i] = empty(i);
        for (int i = M-1; i > 0; --i) TT[i] = combine(TT[2*i],TT[2*i+1]);

        auto rebuild = [&](int i) {
            TT[M+i] = build(i);
            i = (i+M)/2;
            while (i) {
                TT[i] = combine(TT[2*i],TT[2*i+1]);
                i /= 2;
            }
        };

        FF ans = 0;
        for (auto ev: Events) {
            Fraction F = get<0>(ev);
            int j = get<1>(ev);
            int t = get<2>(ev);
            FF prob = 1;
            bool goingRight = false;
            int meetingSince = 0;
            bool origLeftJ = MustBeLeft[j];
            bool origRightJ = MustBeRight[j];
            bool origLeftJ1 = MustBeLeft[j+1];
            bool origRightJ1 = MustBeRight[j+1];
            bool nowRightJ = t != 2;
            bool nowLeftJ1 = t != 3;
            bool fail = false;
            if (nowRightJ && origLeftJ) fail = true;
            if (!nowRightJ && origRightJ) fail = true;
            if (nowLeftJ1 && origRightJ1) fail = true;
            if (!nowLeftJ1 && origLeftJ1) fail = true;
            if (t == 1) {
                MustBeRight[j] = true;
                MustBeLeft[j+1] = true;
            } else if (t == 2) {
                MustBeLeft[j] = true;
                MustBeLeft[j+1] = true;
            } else {
                MustBeRight[j] = true;
                MustBeRight[j+1] = true;
            }

            rebuild(j); rebuild(j+1);

            if (!fail) {
                FF smart = TT[1].x[0] + TT[1].x[1] + TT[1].x[2] + TT[1].x[3];
                ans += smart * (F.u % 998244353) / F.v;
            }

            MustBeLeft[j] = origLeftJ;
            MustBeRight[j] = origRightJ;
            MustBeLeft[j+1] = origLeftJ1;
            MustBeRight[j+1] = origRightJ1;

            if (t == 1) {
                Meet[j] = true;
            } else if (t == 2) {
                MustBeRight[j+1] = true;
                if (MustBeLeft[j+1]) break;
            } else {
                MustBeLeft[j] = true;
                if (MustBeRight[j]) break;
            }

            rebuild(j); rebuild(j+1);
        }

        cout << ans / FF{100}.pow(N) << '\n';
    }
};
