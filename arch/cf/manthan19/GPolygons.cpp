#include "../l/lib.h"

class GPolygons {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> S(N+1, 0);
        for (int i = 2; i <= N; ++i) {
            if (S[i] == 0) {
                for (int j = i; j <= N; j += i) S[j] = i;
            }
        }
        vector<int> C(N+1, 0);
        C[1] = 1;
        for (int i = 2; i <= N; ++i) {
            int j = i, k = i;
            while (j != 1) {
                int p = S[j];
                while (S[j] == p) j /= p;
                k /= p;
                k *= p-1;
            }
            C[i] = k;
        }
//        for (int i = 1; i <= N; ++i) {
//            for (int j = 2; j*i <= N; ++j) {
//                int k = j*i;
//                if (C[k] < C[i]) {
//                    cout << i << ' ' << k << ' ' << C[i] << ' ' << C[k] << endl;
//                    return;
//                }
//            }
//        }


        vector<int> CO;
        for (int i = 1; i <= N; i += 2) {
            CO.push_back(C[i]);
        }
        sort(CO.begin(),CO.end());
        ll allOdd = 0;
        if (CO.size() >= K+1) {
            for (int i = 0; i <= K; ++i) allOdd += CO[i];
        }

        sort(C.begin(),C.end());
        ll ans = 0;
        for (int i = 0; i < 3+K; ++i) ans += C[i];
        if (allOdd != 0) ans = min(ans, allOdd);
        cout << ans << endl;
    }
};
