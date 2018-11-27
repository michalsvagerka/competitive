#include "../l/lib.h"
 #include "../l/random.h"

class TaskG {
public:
    int N, M;

    int simulate(int s, int t) {
        while (t > 0) {
            if (s < M) s = (s + t) % N;
            else s = (s + N - t) % N;
            --t;
        }
        return s;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        int S; ll T;
        cin >> S >> T;
        --S;
        S = simulate(S, T % N);
        vector<pair<int,ll>> C(N, {-1,0LL});
        bool quick = true;
        for (ll i = T/N-1; i >= 0; --i) {
            if (C[S].x != -1) {
                if (quick) {
                    ll diff = C[S].y - i;
                    i %= diff;
                    quick = false;
                }
            } else {
                C[S] = {simulate(S, N-1), i};
            }

            S = C[S].x;
        }
        cout << S+1 << '\n';


//        cin >> N >> M;
//        while (true) {
//            N = random_int{1000, 5000}(rng);
//            M = random_int{1, N-1}(rng);
//            vector<int> H(N), C(N);
//            for (int i = 0; i < N; ++i) H[i] = simulate(i, N);
//
//            for (int i = 0; i < N; ++i) {
//                set<int> U{i};
//                int j = H[i];
//                while (U.find(j) == U.end()) { U.insert(j); j = H[j]; }
//                C[i] = U.size();
//            }
//            int mx = *max_element(C.begin(),C.end());
//            if (mx > 5) cerr << N << ' ' << M << ' ' << mx << endl;
//
//        }
    }
};
