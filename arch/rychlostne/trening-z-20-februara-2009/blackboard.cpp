#include "../l/lib.h"
#include "../l/random.h"

class blackboard {
public:
    ll brute(int N, int K, int R) {
        vector<ll> Z(N);
        for (int i = 0; i < N; ++i) Z[i] = i+1;

        int l = 0;
        for (int i = 0; i < R; ++i) {
            ll a = 0;
            for (int j = l; j < min(l+K, (int)Z.size()); ++j) a += Z[j];
            l = min(l+K,(int)Z.size());
            Z.push_back(a);
        }
        return Z.back();
    }

    ll solve(ll N, ll K, ll R) {
        if (K == 1) return 1+(R-1)%N;
        vector<pair<int,pair<ll,ll>>> Z{{N,{1ll,1ll}}};
        int i = 0;
        while (true) {
            if (Z[i].x == 1 && i == Z.size() - 1) return Z[i].y.x;
            if (Z[i].x >= K) {
                Z.push_back({Z[i].x / K, {K*(2*Z[i].y.x+(K-1)*Z[i].y.y)/2, K*K*Z[i].y.y}});
                if (R <= Z[i].x / K) return Z.back().y.x + Z.back().y.y * (R-1);
                R -= Z[i].x / K;
                Z[i].y.x += (Z[i].x - Z[i].x % K) * Z[i].y.y;
                Z[i].x %= K;
            }

            if (Z[i].x > 0) {
                ll a = 0;
                int l = 0;
                while (true) {
                    if (l == K) break;
                    if (Z[i].x == 0) ++i;
                    if (i == Z.size()) break;
                    int c = min(Z[i].x, int(K-l));
                    l += c;
                    a += c*(2*Z[i].y.x+Z[i].y.y*(c-1))/2;
                    Z[i].x -= c;
                    Z[i].y.x += c*Z[i].y.y;
                }
                Z.push_back({1, {a,0ll}});
                if (!--R) return a;
            } else ++i;
        }
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;

//        random_int NR(1, 100000), KR(1,5000), RR(1,1000);
//        for (int i = 0; i < 100000; ++i) {
//            int N = NR(rng), K = KR(rng), R = RR(rng);
//            ll a1 = solve(N, K, R);
//            ll a2 = brute(N, K, R);
//            if (a1 != a2) cout << "FAIL " << N << ' ' << K << ' ' << R << ' ' << a1 << ' ' << a2 << endl;
//            //else cerr << "OK\n";
//        }

        for (int t = 0; t < T; ++t) {
            //cerr << "Test " << t << endl;
            int N, K, R; cin >> N >> K >> R;
            cout << solve(N,K,R) << '\n';
        }
    }
};
