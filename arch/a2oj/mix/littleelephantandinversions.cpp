#include "../../../l/lib.h"
 #include "../../../l/fenwick.h"
#include <numeric>

class littleelephantandinversions {
public:
    int inv(vector<int>&A, int N) {
        Fenwick<int> F(N+1, 0);
        int x = 0;
        for (int&a:A) {
            x += F.range(a+1,N);
            F.add(a, 1);
        }
        return x;
    }

    int brute(const vector<int>&A, int N, int K) {
        int ans = 0;
        for (int l = 0; l < A.size(); ++l) {
            for (int r = l+1; r < A.size(); ++r) {
                vector<int> Z;
                for (int j = 0; j < A.size(); ++j) {
                    if (j <= l || j >= r) {
                        Z.push_back(A[j]);
                    }
                }
                if (inv(Z, N) <= K) ans++;
            }
        }
        return ans;
    }

    void all(int N) {
        vector<int> A(N);
        iota(A.begin(),A.end(),0);
        do {
            for (int K = 0; K <= N*(N-1)/2; ++K) {
                int s = brute(A, N, K);
                int t = solve(A, N, K);
                if (s != t) {
                    cerr << K << ' ' << s << ' ' << t << ' ' << A;
                }
            }
        } while (next_permutation(A.begin(),A.end()));
    }

    ll solve(vector<int> &A, int N, ll K) {

        Fenwick<int> F1(N+1, 0), F2(N+1, 0);
        vector<int> Prev, Succ;
        ll x = 0;
        for (int a:A) {
            int z = F1.range(a+1, N);
            Prev.push_back(z);
            x += z;
            F1.add(a, 1);
        }
        reverse(A.begin(),A.end());
        for (int&a:A) {
            Succ.push_back(a?F2.range(0,a-1):0);
            F2.add(a, 1);
        }
        reverse(A.begin(),A.end());
        reverse(Succ.begin(),Succ.end());

        if (x <= K) {
            return ll(N)*(N-1)/2;
        } else {
            Fenwick<int> G(N+1, 0);
            int e = 0;
            ll cur = x;
            ll ans = 0;
            for (int b = 0; b < N; ++b) {
                while (e < N && cur > K) {
                    cur -= Prev[e];
                    cur -= Succ[e];
                    cur += G.range(A[e]+1, N);
                    G.add(A[e], 1);
                    e++;
                }

                if (b != 0 && e != N) {
                    ans += N-e;
                }

                if (A[b] != 0) cur -= G.range(0, A[b]-1);
                cur += Prev[b];
                cur += Succ[b];
                G.add(A[b], -1);
            }

            return ans;
        }
    }

    void solve(istream& cin, ostream& cout) {
//        all(8);

        int N; ll K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        set<int> B;
        for (int a:A) B.insert(a);
        map<int,int> C; int i = 0;
        for (int b:B) C[b] = i++;
        for (int&a:A) a = C[a];

        cout << solve(A, N, K) << endl;
    }
};
