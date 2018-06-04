#include "../../../l/lib.h"
#include "../../../l/segtree.h"

vector<vector<pii>> Z;

class seregaandfun {
public:
    struct Segment {
        int J, G;
        int L, R;
        vector<int> A;

        Segment(int j, int g, int l, int r, const vector<int>&W) : J(j), G(g), L(l), R(r), A(r-l) {
            for (int j = l; j < R; ++j) {
                int a = A[j-l] = W[j];
                if (Z[J][a].y == G) Z[J][a].x++;
                else Z[J][a] = {1,G};
            }
        }

        int get(int x) {
            if (x >= L && x < R) return A[x-L];
            else return -1;
        }

        void erase(int x) {
            if (x < L) { --L; --R; }
            else if (x < R) {
                Z[J][A[x-L]].x--;
                A.erase(A.begin()+x-L);
                --R;
            }
        }

        void insert(int x, int a) {
            if (x < L) { ++L; ++R; }
            else if (x < R) {
                if (Z[J][a].y == G) Z[J][a].x++;
                else Z[J][a] = {1, G};
                A.insert(A.begin()+x-L, a);
                ++R;
            }
        }

        int count(int l, int r, int k) {
            if (r < L || l >= R) return 0;
            if (l <= L && r >= R-1) return (Z[J][k].y == G ? Z[J][k].x : 0);
            else {
                int cnt = 0;
                for (int i = max(0,l-L); i <= min(r,R-1)-L; ++i) cnt += (A[i] == k);
                return cnt;
            }
        }
    };

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int blockSize = max(1,int(sqrt(N)));
        vector<int> A(N); cin >> A;
        vector<Segment> S;
        Z = vector2<pii>((N-1)/blockSize+1, N+1, {0,0});
        int g = 0;
        for (int i = 0; i < N; i+=blockSize) { S.emplace_back(i/blockSize, g, i, min(i+blockSize, N), A); }


        int Q; cin >> Q;
        int ans = 0;
        for (int q = 0; q < Q; ++q) {
            int t, l, r; cin >> t >> l >> r;
            l = (l+ans-1)%N + 1;
            r = (r+ans-1)%N + 1;
            if (l > r) swap(l,r);

            --l; --r;
            if (t == 1) {
                if (l == r) continue;

                int z = -1;
                for (auto&s:S) z = max(z, s.get(r));
                for (auto&s:S) s.erase(r);
                for (auto&s:S) s.insert(l, z);

                z = 0;
                for (auto&s:S) z = max(z, (int)s.A.size());
                if (z >= 3*blockSize) {
                    A.clear();
                    A.reserve(N);
                    for (auto&s:S) for (auto &a:s.A) A.push_back(a);
                    S.clear();
                    ++g;
                    for (int i = 0; i < N; i+=blockSize) { S.emplace_back(i/blockSize, g, i, min(i+blockSize, N), A); }
                }

            } else {
                int k; cin >> k;
                k = (k+ans-1)%N + 1;

                ans = 0;
                for (auto&s:S) ans += s.count(l, r, k);
                cout << ans << '\n';
            }
        }
    }
};
