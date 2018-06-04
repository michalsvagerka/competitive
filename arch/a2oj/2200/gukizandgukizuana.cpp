#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int inf = 1e9+1;
class gukizandgukizuana {
public:
    struct Strip {
        int L, R;
        int X;
        vector<int> A;
        unordered_map<int, int> Left;
        unordered_map<int, int> Right;

        Strip(const vector<int> &X, int l, int r) : L(l), R(r), X(0), A(R-L) {
            for (int i = 0; i < A.size(); ++i) A[i] = X[i+L];
            recalc();
        }

        void recalc() {
            Left.clear(); Right.clear();
            for (int i = 0; i < A.size(); ++i) Right[A[i]] = i+L;
            for (int i = (int)A.size()-1; i >= 0; --i) Left[A[i]] = i+L;
        }

        void increase(int l, int r, int x) {
            if (X == inf) return;
            else if (l <= L && r >= R) X = min(inf, X+x);
            else if (l >= R || r <= L) return;
            else {
                if (X) for (int i = 0; i < A.size(); ++i) A[i] = min(inf, A[i] + X);
                for (int i = max(l, L) - L; i < min(r, R) - L; ++i) A[i] = min(inf, A[i] + x);
                X = 0;
                recalc();
            }
        }

        int left(int y) const {
            if (X==inf) return inf;
            auto it = Left.find(y-X);
            return it != Left.end() ? it->y : inf;
        }

        int right(int y) const {
            if (X==inf) return -1;
            auto it = Right.find(y-X);
            return it != Right.end() ? it->y : -1;
        }
    };

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        constexpr int BLOCK = 600;
        vector<Strip> S;
        for (int i = 0; i < N; i+=BLOCK) S.emplace_back(A, i, min(i+BLOCK, N));

        for (int i = 0; i < M; ++i) {
            int t; cin >> t;
            if (t == 1) {
                int l, r, x; cin >> l >> r >> x;
                for (auto&s:S) {
                    s.increase(l-1, r, x);
                }
            } else {
                int l = inf, r = -1;
                int y; cin >> y;
                for (auto&s:S) {
                    l = min(l, s.left(y));
                    r = max(r, s.right(y));
                }
                cout << (r == -1 ? -1 : r-l) << '\n';
            }
        }

    }
};
