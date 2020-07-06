#include "../l/lib.h"
#include "../l/random.h"

int Sol[1<<20], A[1<<20];
class CDrazilLikesHeap {
public:
    int H, G, J;

    bool f(int i, int d) {
        int l = 2*i;
        int r = 2*i+1;
        if (d == H || (A[l] == 0 && A[r] == 0)) {
            if (d <= G) return false;
            A[i] = 0;
            return true;
        } else if (A[l] > A[r]) {
            int al = A[l];
            if (f(l,d+1)) {
                A[i] = al;
                return true;
            } else {
                return false;
            }
        } else {
            int ar = A[r];
            if (f(r,d+1)) {
                A[i] = ar;
                return true;
            } else {
                return false;
            }
        }
    }

    void solve(int i, int d) {
        if (d > G) return;

        while (f(i,d)) {
            Sol[J++] = i;
        }

        solve(2*i, d+1);
        solve(2*i+1, d+1);
    }

    void solve(istream& cin, ostream& cout) {
//        for (int t = 0; t < 10; ++t) {
//            H = 20;
//            G = 1;
//            J = 0;
//            random_int RNG(1, 100);
//            A[0] = 10000000;
//            for (int i = 1; i < (1 << H); ++i) {
//                A[i] = A[i / 2] - RNG(rng);
//            }
//            solve(1, 1);
//        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> H >> G;
            for (int i = 1; i < (1<<H); ++i) cin >> A[i];
            J = 0;

            solve(1,1);
            ll tot = 0;
            for (int i = 1; i < (1<<G); ++i) tot += A[i];

            int cnt = (1<<H)-(1<<G);

            cout << tot << '\n';
            for (int i = 0; i < cnt; ++i) cout << Sol[i] << " \n"[i==cnt-1];
        }
    }
};
