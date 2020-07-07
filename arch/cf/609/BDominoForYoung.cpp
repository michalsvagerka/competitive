#include "../../../l/lib.h"

class BDominoForYoung {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        ll a = 0, b = 0;
        for (int i = 0; i < N; ++i) {
            if (i%2 == 0) {
                a += (A[i]+1)/2;
                b += A[i]/2;
            } else {
                b += (A[i]+1)/2;
                a += A[i]/2;
            }
        }
        
        cout << min(a,b) << endl;
        
//        vector2<ll> D(N+1, 3, -1e18);
//        D[0][0] = 0;
//        for (int i = 0; i < N; ++i) {
//            for (int prev = 0; prev <= 2; ++prev) {
//                for (int next = 0; next <= 2; ++next) {
//                    if (next > A[i]) continue;
//                    D[i+1][next] = max(D[i+1][next], D[i][prev] + (A[i]-next)/2);
//                    if (next != prev && prev != 0 && prev <= A[i]) {
//                        D[i+1][next] = max(D[i+1][next], D[i][prev] + 1 + (A[i]-max(next,prev))/2);
//                    }
//                }
//            }
//        }
//
//        cout << *max_element(D[N].begin(),D[N].end()) << endl;
    }
};
