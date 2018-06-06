#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int SIZE = 1500;
vector<int> Lucky;
vector<bool> LCC;

class luckyarray {
public:

    struct Segment {
        int L,R,Delta;
        vector<int> A, C;

        Segment(int l, int r, const vector<int> &X) : L(l), R(r), Delta(0), A(r-l), C(1e4+1, 0) {
            for (int i = l; i < r; ++i) C[A[i-l] = X[i]]++;
        }

        void add(int l, int r, int x) {
            if (r <= L || l >= R) return;
            if (l <= L && r >= R) Delta += x;
            else {
                for (int i = L; i < R; ++i) C[A[i-L]]--;

                for (int i = max(l,L); i < min(r,R); ++i) A[i-L] += x;
                for (int i = L; i < R; ++i) A[i-L] += Delta;
                Delta = 0;

                for (int a:A) C[a]++;
            }
        }

        int countLucky(int l,int r) {
            int ans = 0;
            if (r <= L || l >= R) return 0;
            if (l <= L && r >= R) {
                for (int l:Lucky) {
                    ans += l >= Delta ? C[l - Delta] : 0;
                }
            } else {
                for (int i = max(l,L); i < min(r,R); ++i) {
                    ans += LCC[A[i-L]+Delta];
                }
            }

            return ans;
        }
    };

    void solve(istream& cin, ostream& cout) {
        Lucky = {4,7,44,47,74,77,444,447,474,477,744,747,774,777,4444,4447,4474,4477,4744,4747,4774,4777,7444,7447,7474,7477,7744,7747,7774,7777};
        LCC = vector<bool>(10001, false);
        for (int &l: Lucky) LCC[l] = true;

        int N, Q; cin >> N >>  Q;
        vector<int> A(N); cin >> A;
        vector<Segment> S;
        for (int i = 0; i < N; i+=SIZE) S.emplace_back(i,min(i+SIZE,N),A);

        for (int q = 0; q < Q; ++q) {
            string s;
            int l,r; cin >> s >> l >> r;
            --l;
            if (s[0] == 'a') {
                int d; cin >> d;
                for (int i = l/SIZE; i <= (r-1)/SIZE; ++i) S[i].add(l,r,d);
            } else {
                int ans = 0;
                for (int i = l/SIZE; i <= (r-1)/SIZE; ++i) ans += S[i].countLucky(l,r);
                cout << ans << '\n';
            }
        }
    }
};
