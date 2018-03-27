#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    void solve(istream& cin, ostream& cout) {
        ll N; cin >> N;
         int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            ll x; cin >> x; --x;
            int p = 0;
            ll prev = 0;
            ll len = N;
            for (int b = 0; b < 62; ++b) {
                if ((x&1) == p) {
                    cout << prev + (x>>1) + 1 << endl;
                    break;
                }

                x >>= 1;
                ll curLen = (len+1-p)/2;
                p = p^(len%2);
                len = len - curLen;

                prev += curLen;
            }
        }

//
//        int p = 0;
//        ll prev = 0;
//        ll len = N;
//        for (int b = 0; b < 62; ++b) {
//            cerr << len << ' ' << p << endl;
//
//            ll curLen = (len+1-p)/2;
//            p = (len%2)^p;
//            len = len - curLen;
//
//            prev += curLen;
//        }




//        vector<int> Q(2*N, 0);
//        for (int i = 0; i < N; ++i) {
//            Q[2*i] = i+1;
//        }
//
//        for (int z = 2*N-1; z >= N; --z) {
//            if (Q[z] != 0) {
//                int y = z;
//                while (Q[y] != 0) --y;
//                swap(Q[z],Q[y]);
//            }
//        }
//
//        for (int i = 0; i < N; ++i) {
//            cout << i+1 << endl;
//        }
//
//        for (int i = 0; i < N; ++i) {
//            cout << Q[i] << endl;
//        }
    }
};
