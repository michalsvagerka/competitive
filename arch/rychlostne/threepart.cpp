#include <unordered_set>
#include "../l/lib.h"
// #include "../l/mod.h"

typedef unsigned long long ull;
class threepart {
public:
    unordered_set<ull> C;
    vector<pair<ull,ull>> R;
    ull z;

    inline int lg(ull x) {
        return 64 - __builtin_clzll(x);
    }

    inline bool solve(ull X) {
        ++z;
        if (X == 0) return true;
        int put = lg(X);
        X ^= 1ULL<<(put-1);
        for (ull b = 1ULL<<(put-2), c = 1ULL; b > c; b>>=1, c<<=1)
            if ((X&b) && (X&c) && solve(X^c^b)) {
                R[__builtin_popcountll(X)/3] = {b,c}; return true;
            }
        return false;
    }

    void solve(istream& cin, ostream& cout) {
        z = 0;
        int N; cin >> N;
        R.resize(N);
        /* if (N==21) {
            cout << "\n"
                    "62 59 57 54 51 49 46 35 34 33 29 32 24 22 23 31 28 25 30 26 27\n"
                    "1 2 3 4 5 6 7 17 16 15 18 13 20 21 19 10 12 14 8 11 9\n"
                    "63 61 60 58 56 55 53 52 50 48 47 45 44 43 42 41 40 39 38 37 36\n";
        } else if (N == 17) {
            cout << "50 47 45 42 39 34 28 26 27 22 20 18 23 25 19 24 21\n"
                    "1 2 3 4 5 9 13 14 11 15 16 17 10 7 12 6 8\n"
                    "51 49 48 46 44 43 41 40 38 37 36 35 33 32 31 30 29\n";
        } else if (N==16) {
            cout << "47 44 42 39 36 29 26 24 25 19 17 18 23 21 22 20\n"
                    "1 2 3 4 5 11 12 13 10 15 16 14 8 9 6 7\n"
                    "48 46 45 43 41 40 38 37 35 34 33 32 31 30 28 27\n";
        } else if (N==20) {
            cout << "59 56 54 51 48 46 40 33 32 31 27 25 23 21 28 30 24 29 26 22\n"
                    "1 2 3 4 5 6 10 16 15 14 17 18 19 20 11 8 13 7 9 12\n"
                    "60 58 57 55 53 52 50 49 47 45 44 43 42 41 39 38 37 36 35 34\n";
        } else */
        if (N%4==3 || N%4==2) { cout << -1 << endl; }
        else if (solve((1ULL<<(3*N))-1)) {
            for (int i = 0; i < N; ++i) cout << lg(R[i].x) << " \n"[i==N-1];
            for (int i = 0; i < N; ++i) cout << lg(R[i].y) << " \n"[i==N-1];
            for (int i = 0; i < N; ++i) cout << lg(R[i].x)+lg(R[i].y) << " \n"[i==N-1];
            cerr << z << endl;
        }
    }
};
